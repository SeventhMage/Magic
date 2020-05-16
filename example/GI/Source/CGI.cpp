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
    
    //camera init
    ISceneNode *cameraNode = pRootNode->CreateChildNode();
    IGameObject *cameraObject = cameraNode->AddGameObject();
    cameraNode->SetPosition(CVector3(0, 0, 5));
    CCameraComponent *pCamera = cameraObject->AddComponent<CCameraComponent>();
    pCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    pCamera->SetClearColor(1.0f, 1.0f, 1.0f, 1.f);
    pCamera->SetClearBit(MAGIC_COLOR_BUFFER_BIT | MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT);
    renderTarget = renderer->CreateRenderTarget(512, 512 / aspect, true, 3);
    pCamera->SetRenderTarget(renderTarget);
    
    //box init
    ISceneNode *boxNode = pRootNode->CreateChildNode();
    IGameObject *boxObject = boxNode->AddGameObject();
    CMeshRendererComponent *pMeshRenderer = boxObject->AddComponent<CMeshRendererComponent>();
    boxMesh = (IMesh *)resourceMgr->LoadResource("resource/mesh/cube.mesh.xml", EResourceType::Mesh);
    
    boxMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/multarget.mat.xml", EResourceType::Material);
    pMeshRenderer->Initialize(mc->GetRenderer(), pCamera->GetFlag(), boxMesh, boxMaterial);
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
    CMeshRendererComponent *pSphereMeshRenderer = sphereObject->AddComponent<CMeshRendererComponent>();
    pSphereMeshRenderer->Initialize(mc->GetRenderer(), pCamera->GetFlag(), sphereMesh, sphereMaterial);
    for (int i=0; i<sphereMaterial->GetImageCount(); ++i)
    {
        IImage *pImage = sphereMaterial->GetImage(i);
        if (pImage)
        {
            sphereTexture = renderer->CreateTexture(pImage->GetComponents(), pImage->GetWidth(), pImage->GetHeight(), pImage->GetFormat(), pImage->GetPixelType(), pImage->GetData());
        }
        pSphereMeshRenderer->SetTexture(i, sphereTexture);
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
