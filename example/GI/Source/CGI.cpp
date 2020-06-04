#include "CGI.h"
#include "math/CVector3.h"
#include "base/magicDef.h"
#include "resource/CSphere.h"

namespace magic
{

CVector3 pos;
float flag = 0.02f;
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
    esContext->screenResolutionRatio = 1.0f;
    mc = CreateMagic(esContext, "gi", 200, 100);
    mc->SetMaxFPS(120);
    esContext->maxFps = mc->GetMaxFPS();
    
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
    float ambientLightColor[] = {0.2f, 0.2f, 0.2f};
    //float directionalLightDir[] = {0.f, -1.f, 1.f};
    float directionalLightColor[] = {.8f, 0.8f, 0.8f};
    float pointLightPosition[] = {0, 10, 0};
    float pointLightColor[] = {.4f, 0.4f, 0.4f};
    float specCoefficient = 400.f;
    CVector4 red(1, 0, 0, 1);
    CVector4 white(1, 1, 1, 1);
    CVector3 directionalLightRotation(DEG_TO_RAD(-0.f), DEG_TO_RAD(-0.f), 0.f);
    CVector3 directionalLightDir(0, 0, -1);
    directionalLightDir.rotateYZBy(DEG_TO_RAD(-0.f));
    directionalLightDir.rotateXZBy(DEG_TO_RAD(-0.f));
    directionalLightDir.normalize();
    CVector3 directionalLightPos = -directionalLightDir * 400;
    //CVector3 directionalLightRotation(DEG_TO_RAD(0.f), DEG_TO_RAD(0.f), 0.f);
    
    renderer = mc->GetRenderer();
    float aspect = 1.f * esContext->width / esContext->height;
    IResourceManager *resourceMgr = mc->GetResourceManager();
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    sceneMgr = mc->GetSceneManager();
    IScene *pScene = sceneMgr->LoadScene();
    ISceneNode *pRootNode = pScene->GetRootNode();
    
    //render target
    renderTarget = renderer->CreateRenderTarget(esContext->width, esContext->height, true, 3);
    vplTarget = renderer->CreateRenderTarget(esContext->width * 0.2, esContext->height * 0.2, true, 3);
    indirectTarget = renderer->CreateRenderTarget(esContext->width * 0.2f, esContext->height * 0.2f, false, 1);
    
    //camera init
    ISceneNode *cameraNode = pRootNode->CreateChildNode();
    IGameObject *cameraObject = cameraNode->AddGameObject();
    cameraNode->SetPosition(CVector3(0, 100, 400));
    CCameraComponent *pCamera = cameraObject->AddComponent<CCameraComponent>();
    pCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 10000.f);
    pCamera->SetClearColor(0.0f, 0.0f, 0.0f, 0.f);
    pCamera->SetClearBit(MAGIC_COLOR_BUFFER_BIT | MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT);
    pCamera->SetRenderTarget(renderTarget);
    
    ISceneNode *vplCameraNode = pRootNode->CreateChildNode();
    IGameObject *vplCameraObject = vplCameraNode->AddGameObject();
    vplCameraNode->SetPosition(directionalLightPos);
    vplCameraNode->SetRotation(directionalLightRotation);
    vplCameraNode->Update();
    CCameraComponent *vplCamera = vplCameraObject->AddComponent<CCameraComponent>();
    //vplCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    vplCamera->Initialize(renderer, CCameraComponent::Ortho, 2000.f, 2000.f / aspect, -10000.f, 10000.f);
    vplCamera->SetClearColor(0.0f, 0.0f, 0.0f, 0.f);
    vplCamera->SetClearBit(MAGIC_COLOR_BUFFER_BIT | MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT);
    vplCamera->SetRenderTarget(vplTarget);
    
    
    //box init
    
    boxMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/multarget.mat.xml", EResourceType::Material);
    uint textureUnit = 0;
    boxMaterial->SetProperty("textureUnit", &textureUnit, sizeof(textureUnit));
    boxMaterial->SetProperty("_color", white.v, sizeof(CVector4));
    boxMaterial->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
    boxMaterial->SetProperty("directionalLightDir", directionalLightDir.v, sizeof(directionalLightDir));
    boxMaterial->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
    boxMaterial->SetProperty("pointLightPosition", pointLightPosition, sizeof(pointLightPosition));
    boxMaterial->SetProperty("pointLightColor", pointLightColor, sizeof(pointLightColor));
    boxMaterial->SetProperty("specCoefficient", &specCoefficient, sizeof(specCoefficient));
    
    IModel *pModel = (IModel *)resourceMgr->LoadResource("resource/model/interiorroom/interior.obj", EResourceType::Model);
    ISceneNode *boxNode = pRootNode->CreateChildNode();
    boxNode->SetPosition(CVector3(-1.f, 0, 0));
    for (int i=0; i<pModel->GetMeshCount(); ++i)
    {
        IGameObject *boxObject = boxNode->AddGameObject();
        CMeshRendererComponent *pMeshRenderer = boxObject->AddComponent<CMeshRendererComponent>();
        boxMesh = pModel->GetMesh(i);//(IMesh *)resourceMgr->LoadResource("resource/mesh/cube.mesh.xml", EResourceType::Mesh);
        //boxMesh = new CSphere(1.5, 20, 20);
        
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
    }
    
    //sphere init
    ISceneNode *sphereNode = pRootNode->CreateChildNode();
    sphereNode->SetPosition(CVector3(.5f, 10, 0));
    IGameObject *sphereObject = sphereNode->AddGameObject();
    sphereMesh = new CSphere(50, 20, 20);
    sphereMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/multarget.mat.xml", EResourceType::Material);
    
    sphereMaterial->SetProperty("textureUnit", &textureUnit, sizeof(textureUnit));
    sphereMaterial->SetProperty("_color", red.v, sizeof(CVector4));
    sphereMaterial->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
    sphereMaterial->SetProperty("directionalLightDir", directionalLightDir.v, sizeof(directionalLightDir));
    sphereMaterial->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
    sphereMaterial->SetProperty("pointLightPosition", pointLightPosition, sizeof(pointLightPosition));
    sphereMaterial->SetProperty("pointLightColor", pointLightColor, sizeof(pointLightColor));
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
    static const int RAND_WIDTH = 16;
    static const int RAND_NUM = RAND_WIDTH * RAND_WIDTH;
    byte vRandNum[RAND_NUM * 3] = { 0 };
//    for (int i = 0; i < RAND_NUM; ++i)
//    {
//        float randRadius = 1.f * rand() / RAND_MAX;
//        float randRadian = 1.f * rand() / RAND_MAX;
//        float randRadian2 = 1.f * rand() / RAND_MAX;
//        randRadian += randRadian2;
//        vRandNum[3 * i] = (randRadius * sin(PI_2 * randRadian) * 127.f);
//        vRandNum[3 * i + 1] = (randRadius * cos(PI_2 * randRadian) * 127.f);
//    }
    float radius = 128.f;
    srand(time(0));
    for (int i=0; i<RAND_NUM; ++i)
    {
        float theta = PI_2 * rand() / RAND_MAX;
        float phi = PI_2 * rand() / RAND_MAX;
        
        vRandNum[3 * i] = radius * sin(theta) * cos(phi);
        vRandNum[3 * i + 1] = radius * sin(theta) * sin(phi);
        vRandNum[3 * i + 2] = radius * cos(theta);
    }

    ITexture *pRandNumTex = renderer->CreateTexture(RGB, RAND_WIDTH, RAND_WIDTH, RGB, PIXEL_UNSIGNED_BYTE, (void*)vRandNum);

    IGameObject *indirectCamera = vplCameraNode->AddGameObject();
    IGameObject *indirectObject = pRootNode->AddGameObject();
    CCameraComponent *pIndirectCamera = indirectCamera->AddComponent<CCameraComponent>();
    pIndirectCamera->Initialize(renderer, CCameraComponent::Ortho, 2000.f, 2000.f / aspect, -10000.f, 10000.f);
    //pIndirectCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    pIndirectCamera->SetClearColor(.0f, .0f, .0f, 0.0f);
    pIndirectCamera->SetClearBit(MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT | MAGIC_COLOR_BUFFER_BIT);
    pIndirectCamera->SetRenderTarget(indirectTarget);
    CMeshRendererComponent *pIndirectRenderer = indirectObject->AddComponent<CMeshRendererComponent>();
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
        indirectMaterial->SetProperty("tRSMPosition", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tRSMNormal", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tRSMFlux", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tRandNum", &textureUnit, sizeof(textureUnit));++textureUnit;
        indirectMaterial->SetProperty("tDepth", &textureUnit, sizeof(textureUnit));++textureUnit;
        
        indirectMaterial->SetProperty("lightDir", directionalLightDir.v, sizeof(directionalLightDir));
        indirectMaterial->SetProperty("lightColor", directionalLightColor, sizeof(directionalLightColor));
        
        
        int samplingColCount = RAND_WIDTH;
        
        indirectMaterial->SetProperty("samplingColCount", &samplingColCount, sizeof(samplingColCount));
        
        pIndirectRenderer->Initialize(renderer, pIndirectCamera->GetFlag(), indirectMesh, indirectMaterial);
        for (int i=0; i<renderTarget->GetBindTextureCount(); ++i)
        {
            pIndirectRenderer->SetTexture(i, renderTarget->GetBindTexture(i));
        }
        for (int i=0; i<vplTarget->GetBindTextureCount(); ++i)
        {
            pIndirectRenderer->SetTexture(i + renderTarget->GetBindTextureCount(), vplTarget->GetBindTexture(i));
        }
        pIndirectRenderer->SetTexture(renderTarget->GetBindTextureCount() + vplTarget->GetBindTextureCount(), pRandNumTex);
        pIndirectRenderer->SetTexture(renderTarget->GetBindTextureCount() + vplTarget->GetBindTextureCount() + 1, vplTarget->GetDepthTexture());

    }

    
    //deferred shade
    IGameObject *deferredCamera = cameraNode->AddGameObject();
    IGameObject *deferredObject = pRootNode->AddGameObject();
    CCameraComponent *pDeferredCamera = deferredCamera->AddComponent<CCameraComponent>();
    //pDeferredCamera->Initialize(renderer, CCameraComponent::Ortho, 2.f, 2.f / aspect, -100.f, 100.f);
    pDeferredCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    pDeferredCamera->SetClearColor(.0f, 0.0f, .0f, 0.0f);
    pDeferredCamera->SetClearBit(MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT | MAGIC_COLOR_BUFFER_BIT);
    CMeshRendererComponent *pDeferredRenderer = deferredObject->AddComponent<CMeshRendererComponent>();
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
        deferredMaterial->SetProperty("indirectLightTexture", &indirectLight, sizeof(indirectLight));
        
        deferredMaterial->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
        deferredMaterial->SetProperty("directionalLightDir", directionalLightDir.v, sizeof(directionalLightDir));
        deferredMaterial->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
        deferredMaterial->SetProperty("pointLightPosition", pointLightPosition, sizeof(pointLightPosition));
        deferredMaterial->SetProperty("pointLightColor", pointLightColor, sizeof(pointLightColor));
        deferredMaterial->SetProperty("specCoefficient", &specCoefficient, sizeof(specCoefficient));
        pDeferredRenderer->Initialize(renderer, pDeferredCamera->GetFlag(), deferredMesh, deferredMaterial);
        for (int i=0; i<renderTarget->GetBindTextureCount(); ++i)
        {
            pDeferredRenderer->SetTexture(i, renderTarget->GetBindTexture(i));
        }
        
        pDeferredRenderer->SetTexture(renderTarget->GetBindTextureCount(), indirectTarget->GetBindTexture(0));
        pDeferredRenderer->SetTexture(renderTarget->GetBindTextureCount() + 1, vplTarget->GetDepthTexture());
        
    }
    
     
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");
    
    esContext->drawFunc = [=](){
        mc->Run([=]() {
            if (pos.x > 0.6f || pos.x < -0.6f)
                ;//flag = -flag;
            pos.x += flag;
            
            //boxObject->GetSceneNode()->SetRotation(CVector3(0, DEG_TO_RAD(45.f), 0));
            //sphereObject->GetSceneNode()->SetRotation(CVector3(0, rot, 0));
            
            rot += flag;
        });
    };

    esContext->updateFunc = [=]() {

    };

	esContext->keyFunc = [=](unsigned char key, int x, int y) {
		CVector3 spherePosition = sphereNode->GetPosition();
		CVector3 camPos = cameraNode->GetPosition();
		CVector3 dir(0, 0, -1);
		CVector3 right(1, 0, 0);
		CVector3 up(0, 1, 0);
		CMatrix4 transform = cameraNode->GetAbsluateTransform();
		transform.SetTranslation(CVector3(0, 0, 0));
		transform.TransformVect(dir);
		transform.TransformVect(right);
		transform.TransformVect(up);
		dir.normalize();
		right.normalize();
		up.normalize();


		CVector3 rotation = cameraNode->GetRotation();

		float flag = 4.f;
		switch (key)
		{
		case 'W':
		case 'w':
			spherePosition.z -= flag;
			break;
		case 'S':
		case 's':
			spherePosition.z += flag;
			break;
		case 'A':
		case 'a':
			spherePosition.x -= flag;
			break;
		case 'D':
		case 'd':
			spherePosition.x += flag;
			break;
		case 32:
			spherePosition.y += flag;
		case 'Q':
		case 'q':
			spherePosition.y += flag;
			break;
		case 'Z':
		case 'z':
			spherePosition.y -= flag;
		case 'E':
		case 'e':
			spherePosition.y -= flag;
			break;
		case 'I':
		case 'i':
			camPos += dir * flag;
			break;
		case 'K':
		case 'k':
			camPos -= dir * flag;
			break;
		case 'J':
		case 'j':
			camPos -= right * flag;
			break;
		case 'L':
		case 'l':
			camPos += right * flag;
			break;
		case 'U':
		case 'u':
			camPos += up * flag;
			break;
		case 'O':
		case 'o':
			camPos -= up * flag;
			break;
		case 'Y':
			rotation.y += 0.1f;
			break;
		case 'y':
			rotation.y -= 0.1f;
			break;
		case 'G':
		case 'g':
			pIndirectCamera->SetEnable(!pIndirectCamera->IsEnable());
			break;
		case 'P':
		case 'p':
			LogInfo("FPS:%d\n", mc->GetFPS());
			break;
		}
		sphereNode->SetPosition(spherePosition);
		cameraNode->SetPosition(camPos);
		cameraNode->SetRotation(rotation);
	};
    
    esContext->touchMoveFunc = [=](int index, int dx, int dy, int count){
        CVector3 spherePosition = sphereNode->GetPosition();
        if (count == 1)
        {
            float flag = 1.f;
            spherePosition.x += dx > 0 ? flag : -flag;
            spherePosition.y -= dy > 0 ? flag : -flag;
            sphereNode->SetPosition(spherePosition);
            CVector3 pointLightPosition(spherePosition.x, spherePosition.y + 2, spherePosition.z + 2);
            pDeferredRenderer->GetShaderProgram()->SetUniform("pointLightPosition", pointLightPosition.v);
        }
        else if (count == 2)
        {
            float flag = 0.02f;
            CVector3 rotation = cameraNode->GetRotation();
            rotation.y += dx > 0 ? flag : -flag;
            //rotation.x -= dy > 0 ? flag : -flag;
            cameraNode->SetRotation(rotation);
        }
        else if (count == 3)
        {
            float flag = 8.f;
            //CVector3 camPos = vplCameraNode->GetAbslutePosition();
            CVector3 camPos = cameraNode->GetAbslutePosition();
            CVector3 dir(0, 0, -1);
            CMatrix4 transform = cameraNode->GetAbsluateTransform();
            transform.SetTranslation(CVector3(0, 0, 0));
            transform.TransformVect(dir);
            dir.normalize();
            camPos -= dir * (dy > 0 ? flag : -flag);
            cameraNode->SetPosition(camPos);
        }
        
    };

    esContext->shutdownFunc = [=](){
        
    };

}

}
