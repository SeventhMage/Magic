#include "HelloTriangle.h"
#include <stdio.h>

float triangleVertices[][3] = {  0.0f,  0.5f, 0.0f,
                         -0.5f, -0.5f, 0.0f,
                         0.5f, -0.5f, 0.0f
                      };
float triangleColors[][4] = {
    1.0f, 0.8f, 0.8f, 1.0f,
    0.8f, 1.0f, 0.8f, 1.0f,
    .8f, .8f, 1.0f, 1.0f,
};

float triangleTexCoords[][2] = {
    0.5f, 1.f,
    0.f, 0.f,
    1.f, 0.f,
};

float triangleNormals[][3] = {
    0.f, 0.f, 1.f,
    0.f, 0.f, 1.f,
    0.f, 0.f, 1.f,
};

unsigned short triangleIndices[] = {0, 1, 2};

float quadVertices[][3] = {
    -1.f, -1.f, 0.f,
    1.f, -1.f, 0.f,
    1.f, 1.f, 0.f,
    -1.f, 1.f, 0.f,
};

float quadTexCoords[][2] = {
    0.f, 0.f,
    1.f, 0.f,
    1.f, 1.f,
    0.f, 1.f,
};

unsigned short quadIndices[] = {0, 1, 2, 0, 2, 3};

char vQuadShaderStr[] =
 "#version 300 es                          \n"
 "layout(location = 0) in vec3 vPosition;  \n"
 "layout(location = 1) in vec2 vTexCoord;  \n"
 "out vec2 vTex;                           \n"
 "void main()                              \n"
 "{                                        \n"
 "   vTex = vTexCoord;                     \n"
 "   gl_Position = vec4(vPosition, 1.0);   \n"
 "}                                        \n";

char fQuadShaderStr[] =
 "#version 300 es                              \n"
 "precision mediump float;                     \n"
 "uniform sampler2D screenAlignedTexture;      \n"
 "in vec2 vTex;                                \n"
 "out vec4 fragColor;                          \n"
 "void main()                                  \n"
 "{                                            \n"
 "   fragColor = texture(screenAlignedTexture, vTex);   \n"
 "}                                            \n";

float ambientLightColor[] = {0.2f, 0.2f, 0.2f};
float directionalLightDir[] = {1.f, 1.f, 1.f};
float directionalLightColor[] = {0.8f, 0.8f, 0.8f};
float specCoefficient = 10;

CVector3 pos;
float flag = 0.02f;
float rot = 0;

HelloTriangle::HelloTriangle(SRenderContext *content)
{
    //Init(content);
    InitDeferredShade(content);
}

HelloTriangle::~HelloTriangle()
{
    printf("Application end.\n\n");

    printf("Cleaning ... \n");
    delete quadMaterial;
    delete quadMesh;
    
    delete screenTarget;
    delete  deferredObject;
    delete deferredCamera;
    delete deferredMaterial;
    delete deferredMesh;
    
    delete  screenAlignedQuad;
    delete quadCamera;
    delete triangleCamera;
    delete triangle;
    delete renderTarget;
    delete triangleTexture;
    delete triangleMaterial;
    delete triangleMesh;
    sceneMgr->UnloadScene();
    
    Clean();
    printf("Finish clean.\n\n");
}

void HelloTriangle::Init(SRenderContext *esContext)
{
    printf("Start initalizing Engine ... \n");
    mc = CreateMagic(esContext, "Triangle", 1280, 960);
    mc->SetFPS(60);
    renderer = mc->GetRenderer();
    esContext->drawFunc = [=](){

    };
    esContext->updateFunc = [=]() {
        mc->Run([=]() {
            if (pos.x > 0.6f || pos.x < -0.6f)
                flag = -flag;
            pos.x += flag;

            triangle->GetSceneNode()->SetRotation(CVector3(0, rot, 0));

            //triangle.GetSceneNode()->SetPosition(pos);
            rot += flag;
        });
    };

    esContext->shutdownFunc = [=](){
        
    };
    float aspect = 1.f * esContext->width / esContext->height;
    IResourceManager *resourceMgr = mc->GetResourceManager();
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    sceneMgr = mc->GetSceneManager();
    IScene *pScene = sceneMgr->LoadScene();
    ISceneNode *pRootNode = pScene->GetRootNode();
    ISceneNode *cameraNode = pRootNode->CreateChildNode();
    ISceneNode *triangleNode = pRootNode->CreateChildNode();
    triangleCamera = new CGameObject(cameraNode);
    triangle = new CGameObject(triangleNode);
    
    cameraNode->SetPosition(CVector3(0, 0, 2));
    CCameraComponent *pTriangleCamera = triangleCamera->AddComponent<CCameraComponent>();
    
    pTriangleCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    pTriangleCamera->SetClearColor(1.0f, 1.0f, 1.0f, 1.f);
    pTriangleCamera->SetClearBit(MAGIC_COLOR_BUFFER_BIT | MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT);
    renderTarget = renderer->CreateRenderTarget(1024, 1024 / aspect, false, 1);
    pTriangleCamera->SetRenderTarget(renderTarget);
    
    CMeshRendererComponent *pMeshRenderer = triangle->AddComponent<CMeshRendererComponent>();
    
    triangleMesh = new CMesh();
    
    triangleMesh->SetPositions(triangleVertices, sizeof(triangleVertices));
    triangleMesh->SetColors(triangleColors, sizeof(triangleColors));
    triangleMesh->SetUVs(triangleTexCoords, sizeof(triangleTexCoords));
    triangleMesh->SetIndices(triangleIndices, sizeof(triangleIndices));
    triangleMesh->SetNormals(triangleNormals, sizeof(triangleNormals));

    triangleMaterial = new CMaterial(resourceMgr);
    triangleMaterial->SetShader(EShaderType::Vertex, "resource/shader/common.vert");
    triangleMaterial->SetShader(EShaderType::Fragment, "resource/shader/common.frag");
    float colorProperty[] = {0.5f, 0.5f, 0.5f, 1.0f};
    triangleMaterial->SetProperty("color", colorProperty, sizeof(colorProperty));
    triangleMaterial->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
    triangleMaterial->SetProperty("directionalLightDir", directionalLightDir, sizeof(directionalLightDir));
    triangleMaterial->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
    triangleMaterial->SetProperty("specCoefficient", &specCoefficient, sizeof(specCoefficient));
    uint textureUnit = 0;
    triangleMaterial->SetProperty("textureUnit", &textureUnit, sizeof(textureUnit));
    
    CMatrix4 transform = cameraNode->GetAbsluateTransform();
    transform.SetTranslation(CVector3(0, 0, 0));
    CVector3 viewDir(0, 0, 1.f);
    transform.TransformVect(viewDir);
    triangleMaterial->SetProperty("viewDir", viewDir.v, sizeof(viewDir));
    IImage *pImage = (IImage *)resourceMgr->LoadResource("resource/texture/crate.tga", EResourceType::Image);
    
    if (pImage)
    {
        triangleTexture = renderer->CreateTexture(pImage->GetComponents(), pImage->GetWidth(), pImage->GetHeight(), pImage->GetFormat(), pImage->GetPixelType(), pImage->GetData());
    }
    
    pMeshRenderer->Initialize(mc->GetRenderer(), pTriangleCamera->GetFlag(), triangleMesh, triangleMaterial);
    pMeshRenderer->SetTexture(0, triangleTexture);
    
    //screen aligned quad
    quadCamera = new CGameObject(pRootNode);
    screenAlignedQuad = new CGameObject(pRootNode);
    CCameraComponent *pQuadCamera = quadCamera->AddComponent<CCameraComponent>();
    pQuadCamera->Initialize(renderer, CCameraComponent::Ortho, 2.f, 2.f / aspect, -100.f, 100.f);
    pQuadCamera->SetClearColor(.0f, .0f, .0f, .0f);
    pQuadCamera->SetClearBit(MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT | MAGIC_COLOR_BUFFER_BIT);
    CMeshRendererComponent *pSAQMeshRenderer = screenAlignedQuad->AddComponent<CMeshRendererComponent>();
    screenAlignedQuad->SetSceneNode(pRootNode);
    quadMesh = new CMesh();
     
    quadMesh->SetPositions(quadVertices, sizeof(quadVertices));
    quadMesh->SetUVs(quadTexCoords, sizeof(quadTexCoords));
    quadMesh->SetIndices(quadIndices, sizeof(quadIndices));
    
    quadMaterial = new CMaterial(resourceMgr);
    
    if (renderTarget)
    {
        quadMaterial->SetShader(EShaderType::Vertex, vQuadShaderStr, sizeof(vQuadShaderStr));
        quadMaterial->SetShader(EShaderType::Fragment, fQuadShaderStr, sizeof(fQuadShaderStr));
        ITexture *renderTexture = renderTarget->GetBindTexture(0);
        uint textureQuad = 0;
        quadMaterial->SetProperty("screenAlignedTexture", &textureQuad, sizeof(textureQuad));
        pSAQMeshRenderer->Initialize(renderer, pQuadCamera->GetFlag(), quadMesh, quadMaterial);
        pSAQMeshRenderer->SetTexture(0, renderTexture);
    }
     
    resourceMgr->UnloadResource(pImage);
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");
}

void HelloTriangle::InitDeferredShade(SRenderContext *esContext)
{
    printf("Start initalizing Engine ... \n");
    esContext->screenResolutionRatio = 512.f / esContext->width;
    mc = CreateMagic(esContext, "Triangle", 300, 200);
    mc->SetFPS(60);
    esContext->drawFunc = [=](){
    };

    esContext->updateFunc = [=]() {
        mc->Run([=]() {
            if (pos.x > 0.6f || pos.x < -0.6f)
                ;//flag = -flag;
            pos.x += flag;
            
            triangle->GetSceneNode()->SetRotation(CVector3(0, rot, rot));
            
            //triangle.GetSceneNode()->SetPosition(pos);
            rot += flag;
        });
    };

    esContext->shutdownFunc = [=](){
        
    };
    renderer = mc->GetRenderer();
    float aspect = 1.f * esContext->width / esContext->height;
    IResourceManager *resourceMgr = mc->GetResourceManager();
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    sceneMgr = mc->GetSceneManager();
    IScene *pScene = sceneMgr->LoadScene();
    ISceneNode *pRootNode = pScene->GetRootNode();
    ISceneNode *cameraNode = pRootNode->CreateChildNode();
    ISceneNode *triangleNode = pRootNode->CreateChildNode();
    triangleCamera = new CGameObject(cameraNode);
    triangle = new CGameObject(triangleNode);
    
    cameraNode->SetPosition(CVector3(0, 0, 5));
    CCameraComponent *pTriangleCamera = triangleCamera->AddComponent<CCameraComponent>();
    
    pTriangleCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    pTriangleCamera->SetClearColor(1.0f, 1.0f, 1.0f, 1.f);
    pTriangleCamera->SetClearBit(MAGIC_COLOR_BUFFER_BIT | MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT);
    renderTarget = renderer->CreateRenderTarget(512, 512 / aspect, true, 3);
    pTriangleCamera->SetRenderTarget(renderTarget);
    
    CMeshRendererComponent *pMeshRenderer = triangle->AddComponent<CMeshRendererComponent>();
    triangleMesh = (IMesh *)resourceMgr->LoadResource("resource/mesh/triangle.mesh.xml", EResourceType::Mesh);
    
    triangleMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/multarget.mat.xml", EResourceType::Material);
    pMeshRenderer->Initialize(mc->GetRenderer(), pTriangleCamera->GetFlag(), triangleMesh, triangleMaterial);
    for (int i=0; i<triangleMaterial->GetImageCount(); ++i)
    {
        IImage *pImage = triangleMaterial->GetImage(i);
        if (pImage)
        {
            triangleTexture = renderer->CreateTexture(pImage->GetComponents(), pImage->GetWidth(), pImage->GetHeight(), pImage->GetFormat(), pImage->GetPixelType(), pImage->GetData());
        }
        pMeshRenderer->SetTexture(i, triangleTexture);
    }
    
    //deferred shade
    deferredCamera = new CGameObject(pRootNode);
    deferredObject = new CGameObject(pRootNode);
    CCameraComponent *pDeferredCamera = deferredCamera->AddComponent<CCameraComponent>();
    pDeferredCamera->Initialize(renderer, CCameraComponent::Ortho, 2.f, 2.f / aspect, -100.f, 100.f);
    pDeferredCamera->SetClearColor(.0f, .0f, .0f, .0f);
    pDeferredCamera->SetClearBit(MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT | MAGIC_COLOR_BUFFER_BIT);
    CMeshRendererComponent *pDeferredRenderer = deferredObject->AddComponent<CMeshRendererComponent>();
    deferredObject->SetSceneNode(pRootNode);
    deferredMesh = new CMesh();
     
    deferredMesh->SetPositions(quadVertices, sizeof(quadVertices));
    deferredMesh->SetUVs(quadTexCoords, sizeof(quadTexCoords));
    deferredMesh->SetIndices(quadIndices, sizeof(quadIndices));
    
    deferredMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/deferredShade.mat.xml", EResourceType::Material);
    
    if (renderTarget)
    {
        static uint texturePosition = 0;
        static uint textureNormal = 1;
        static uint textureColor = 2;
        deferredMaterial->SetProperty("positionTexture", &texturePosition, sizeof(texturePosition));
        deferredMaterial->SetProperty("normalTexture", &textureNormal, sizeof(textureNormal));
        deferredMaterial->SetProperty("colorTexture", &textureColor, sizeof(textureColor));
        
        deferredMaterial->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
        deferredMaterial->SetProperty("directionalLightDir", directionalLightDir, sizeof(directionalLightDir));
        deferredMaterial->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
        deferredMaterial->SetProperty("specCoefficient", &specCoefficient, sizeof(specCoefficient));
        pDeferredRenderer->Initialize(renderer, pDeferredCamera->GetFlag(), deferredMesh, deferredMaterial);
        for (int i=0; i<renderTarget->GetBindTextureCount(); ++i)
        {
            pDeferredRenderer->SetTexture(i, renderTarget->GetBindTexture(i));
        }
    }
     
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");
    
    
}

