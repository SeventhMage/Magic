#include "CGI.h"
#include "math/CVector3.h"
#include "base/magicDef.h"
#include "resource/CSphere.h"

namespace magic
{

CVector3 pos;
float flag = 0.04f;
float rot = 0;

CGI::CGI()
{
    
}

CGI::~CGI()
{
    printf("Clean ...\n");
    SAFE_DEL(indirectMaterial);
    SAFE_DEL(indirectMesh);
    
    SAFE_DEL(deferredMaterial);
    SAFE_DEL(deferredMesh);
    
    SAFE_DEL(sphereTexture);
    SAFE_DEL(sphereMaterial);
    SAFE_DEL(sphereMesh);
    
    SAFE_DEL(boxTexture);
    SAFE_DEL(boxMaterial);
    SAFE_DEL(boxMesh);
    
    SAFE_DEL(renderTarget);
    CleanMagic();
    printf("Finish Clean.");
}

void CGI::Init(SRenderContext *esContext)
{
    printf("Start initalizing Engine ... \n");
    esContext->screenResolutionRatio = 512.f / esContext->width;
    mc = CreateMagic(esContext, "gi", 300, 200);
    mc->SetFPS(60);
    
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
    float ambientLightColor[] = {0.1f, 0.1f, 0.1f};
    float directionalLightDir[] = {1.f, 1.f, 1.f};
    float directionalLightColor[] = {0.8f, 0.8f, 0.8f};
    float specCoefficient = 10;
    
    renderer = mc->GetRenderer();
    float aspect = 1.f * esContext->width / esContext->height;
    IResourceManager *resourceMgr = mc->GetResourceManager();
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    sceneMgr = mc->GetSceneManager();
    IScene *pScene = sceneMgr->LoadScene();
    ISceneNode *pRootNode = pScene->GetRootNode();
    
    //render target
    renderTarget = renderer->CreateRenderTarget(512, 512 / aspect, true, 3);
    vplTarget = renderer->CreateRenderTarget(512, 512 / aspect, true, 3);
    indirectTarget = renderer->CreateRenderTarget(512, 512 / aspect, false, 1);
    
    //camera init
    ISceneNode *cameraNode = pRootNode->CreateChildNode();
    IGameObject *cameraObject = cameraNode->AddGameObject();
    cameraNode->SetPosition(CVector3(0, 0, 5));
    CCameraComponent *pCamera = cameraObject->AddComponent<CCameraComponent>();
    pCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    pCamera->SetClearColor(1.0f, 1.0f, 1.0f, 1.f);
    pCamera->SetClearBit(MAGIC_COLOR_BUFFER_BIT | MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT);
    pCamera->SetRenderTarget(renderTarget);
    
    ISceneNode *vplCameraNode = pRootNode->CreateChildNode();
    IGameObject *vplCameraObject = vplCameraNode->AddGameObject();
    vplCameraNode->SetPosition(CVector3(1, 1, 1));
    CCameraComponent *vplCamera = vplCameraObject->AddComponent<CCameraComponent>();
    vplCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    vplCamera->SetClearColor(0.0f, 0.0f, 0.0f, 0.f);
    vplCamera->SetClearBit(MAGIC_COLOR_BUFFER_BIT | MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT);
    vplCamera->SetRenderTarget(vplTarget);
    
    
    //box init
    ISceneNode *boxNode = pRootNode->CreateChildNode();
    IGameObject *boxObject = boxNode->AddGameObject();
    CMeshRendererComponent *pMeshRenderer = boxObject->AddComponent<CMeshRendererComponent>();
    boxMesh = (IMesh *)resourceMgr->LoadResource("resource/mesh/cube.mesh.xml", EResourceType::Mesh);
    
    boxMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/multarget.mat.xml", EResourceType::Material);
    uint textureUnit = 0;
    boxMaterial->SetProperty("textureUnit", &textureUnit, sizeof(textureUnit));
    boxMaterial->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
    boxMaterial->SetProperty("directionalLightDir", directionalLightDir, sizeof(directionalLightDir));
    boxMaterial->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
    boxMaterial->SetProperty("specCoefficient", &specCoefficient, sizeof(specCoefficient));
    pMeshRenderer->Initialize(mc->GetRenderer(), pCamera->GetFlag() | vplCamera->GetFlag(), boxMesh, boxMaterial);
    for (int i=0; i<boxMaterial->GetImageCount(); ++i)
    {
        IImage *pImage = boxMaterial->GetImage(i);
        if (pImage)
        {
            boxTexture = renderer->CreateTexture(pImage->GetComponents(), pImage->GetWidth(), pImage->GetHeight(), pImage->GetFormat(), pImage->GetPixelType(), pImage->GetData());
        }
        pMeshRenderer->SetTexture(i, boxTexture);
    }
    
    //sphere init
    ISceneNode *sphereNode = pRootNode->CreateChildNode();
    IGameObject *sphereObject = sphereNode->AddGameObject();
    sphereMesh = new CSphere(0.5, 20, 20);
    sphereMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/multarget.mat.xml", EResourceType::Material);
    sphereMaterial->SetProperty("textureUnit", &textureUnit, sizeof(textureUnit));
    sphereMaterial->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
    sphereMaterial->SetProperty("directionalLightDir", directionalLightDir, sizeof(directionalLightDir));
    sphereMaterial->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
    sphereMaterial->SetProperty("specCoefficient", &specCoefficient, sizeof(specCoefficient));
    CMeshRendererComponent *pSphereMeshRenderer = sphereObject->AddComponent<CMeshRendererComponent>();
    pSphereMeshRenderer->Initialize(mc->GetRenderer(), pCamera->GetFlag() | vplCamera->GetFlag(), sphereMesh, sphereMaterial);
    for (int i=0; i<sphereMaterial->GetImageCount(); ++i)
    {
        IImage *pImage = sphereMaterial->GetImage(i);
        if (pImage)
        {
            sphereTexture = renderer->CreateTexture(pImage->GetComponents(), pImage->GetWidth(), pImage->GetHeight(), pImage->GetFormat(), pImage->GetPixelType(), pImage->GetData());
        }
        pSphereMeshRenderer->SetTexture(i, sphereTexture);
    }
    
    //Indirect light
    IGameObject *indirectCamera = pRootNode->AddGameObject();
    IGameObject *indirectObject = pRootNode->AddGameObject();
    CCameraComponent *pIndirectCamera = indirectCamera->AddComponent<CCameraComponent>();
    pIndirectCamera->Initialize(renderer, CCameraComponent::Ortho, 2.f, 2.f / aspect, -100.f, 100.f);
    pIndirectCamera->SetClearColor(.0f, .0f, .0f, .0f);
    pIndirectCamera->SetClearBit(MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT | MAGIC_COLOR_BUFFER_BIT);
    pIndirectCamera->SetRenderTarget(indirectTarget);
    CMeshRendererComponent *pIndirectRenderer = indirectObject->AddComponent<CMeshRendererComponent>();
    indirectObject->SetSceneNode(pRootNode);
    indirectMesh = new CMesh();
     
    indirectMesh->SetPositions(quadVertices, sizeof(quadVertices));
    indirectMesh->SetUVs(quadTexCoords, sizeof(quadTexCoords));
    indirectMesh->SetIndices(quadIndices, sizeof(quadIndices));
    
    indirectMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/indirectLight.mat.xml", EResourceType::Material);
    
    if (renderTarget && vplTarget)
    {
        uint textureUnit = 0;
        indirectMaterial->SetProperty("tGPosition", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tGNormal", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tGColor", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tRSMFlux", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tRSMPosition", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tRSMNormal", &textureUnit, sizeof(textureUnit));++textureUnit;
        
        indirectMaterial->SetProperty("lightDir", directionalLightDir, sizeof(directionalLightDir));
        indirectMaterial->SetProperty("lightColor", directionalLightColor, sizeof(directionalLightColor));
        int samplingColCount = 64;
        indirectMaterial->SetProperty("samplingColCount", &samplingColCount, sizeof(samplingColCount));
        
        pIndirectRenderer->Initialize(renderer, pIndirectCamera->GetFlag(), deferredMesh, indirectMaterial);
        for (int i=0; i<renderTarget->GetBindTextureCount(); ++i)
        {
            pIndirectRenderer->SetTexture(i, renderTarget->GetBindTexture(i));
        }
        for (int i=0; i<vplTarget->GetBindTextureCount(); ++i)
        {
            pIndirectRenderer->SetTexture(i + renderTarget->GetBindTextureCount(), vplTarget->GetBindTexture(i));
        }
    }

    
    //deferred shade
    IGameObject *deferredCamera = pRootNode->AddGameObject();
    IGameObject *deferredObject = pRootNode->AddGameObject();
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
    
    if (renderTarget && indirectTarget)
    {
        uint texturePosition = 0;
        uint textureNormal = 1;
        uint textureColor = 2;
        uint indirectLight = 3;
        deferredMaterial->SetProperty("positionTexture", &texturePosition, sizeof(texturePosition));
        deferredMaterial->SetProperty("normalTexture", &textureNormal, sizeof(textureNormal));
        deferredMaterial->SetProperty("colorTexture", &textureColor, sizeof(textureColor));
        deferredMaterial->SetProperty("indirectLightColor", &indirectLight, sizeof(indirectLight));
        
        deferredMaterial->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
        deferredMaterial->SetProperty("directionalLightDir", directionalLightDir, sizeof(directionalLightDir));
        deferredMaterial->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
        deferredMaterial->SetProperty("specCoefficient", &specCoefficient, sizeof(specCoefficient));
        pDeferredRenderer->Initialize(renderer, pDeferredCamera->GetFlag(), deferredMesh, deferredMaterial);
        for (int i=0; i<renderTarget->GetBindTextureCount(); ++i)
        {
            pDeferredRenderer->SetTexture(i, renderTarget->GetBindTexture(i));
        }
        
        pDeferredRenderer->SetTexture(renderTarget->GetBindTextureCount(), indirectTarget->GetBindTexture(0));
    }
    

     
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");
    
    esContext->drawFunc = [=](){
    };

    esContext->updateFunc = [=]() {
        mc->Run([=]() {
            if (pos.x > 0.6f || pos.x < -0.6f)
                ;//flag = -flag;
            pos.x += flag;
            
            boxObject->GetSceneNode()->SetRotation(CVector3(0, rot, rot));
            sphereObject->GetSceneNode()->SetRotation(CVector3(0, rot, 0));
            
            rot += flag;
        });
    };

    esContext->shutdownFunc = [=](){
        
    };

}

}
