#include "CGI.h"
#include "math/CVector3.h"
#include "base/magicDef.h"
#include "resource/CSphere.h"

#include <time.h>

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
    mc = CreateMagic(esContext, "gi", 1280, 960);
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
    float ambientLightColor[] = {0.1f, 0.1f, 0.1f};
    //float directionalLightDir[] = {0.f, -1.f, 1.f};
    float directionalLightColor[] = {.8f, 0.8f, 0.8f};
    float pointLightPosition[] = {0, 10, 0};
    float pointLightColor[] = {.4f, 0.4f, 0.4f};
    float specCoefficient = 900.f;
    CVector4 red(1, 0, 0, 1);
    CVector4 white(1, 1, 1, 1);
    CVector3 directionalLightRotation(DEG_TO_RAD(-45.f), DEG_TO_RAD(0.f), 0.f);
    CVector3 directionalLightDir(0, 0, -1);
    directionalLightDir.rotateYZBy(DEG_TO_RAD(-45.f));
    directionalLightDir.rotateXZBy(DEG_TO_RAD(0.f));
    directionalLightDir.normalize();
    CVector3 directionalLightPos = -directionalLightDir * 200;
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
    indirectTarget = renderer->CreateRenderTarget(esContext->width * 0.4f, esContext->height * 0.4f, false, 1);
    
    //camera init
    ISceneNode *cameraNode = pRootNode->CreateChildNode();
    IGameObject *cameraObject = cameraNode->AddGameObject();
    cameraNode->SetPosition(CVector3(20, 100, 450));
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
	vplCamera->Initialize(renderer, CCameraComponent::Ortho, 1000.f, 1000.f / aspect, -10000.f, 10000.f);
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
	
	IModel *pModel = (IModel *)resourceMgr->LoadResource("resource/model/HouseInterior/houseinterior.obj", EResourceType::Model);
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
	sphereNode->SetPosition(CVector3(0.f, 60, 100));
	IGameObject *sphereObject = sphereNode->AddGameObject();
	sphereMesh = new CSphere(40, 20, 20);
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
	
	//srand(time(0));
	static const int RAND_WIDTH = 16;
	static const int RAND_NUM = RAND_WIDTH * RAND_WIDTH;
	byte vRandNum[RAND_NUM * 3] = { 0 };
	/*
    for (int i = 0; i < RAND_NUM; ++i)
    {
        float randRadius = 1.f * rand() / RAND_MAX;
        float randRadian = 1.f * rand() / RAND_MAX;
        float randRadian2 = 1.f * rand() / RAND_MAX;
        randRadian += randRadian2;
        vRandNum[3 * i] = (randRadius * sin(PI_2 * randRadian) * 127.f);
        vRandNum[3 * i + 1] = (randRadius * cos(PI_2 * randRadian) * 127.f);
    }
	*/

	for (int i=0; i<RAND_NUM; ++i)
	{
		float theta = PI_2 * rand() / RAND_MAX;
		float phi = PI_2 * rand() / RAND_MAX;
		float radius = 127.f * rand() / RAND_MAX;
		vRandNum[3 * i] = radius * sin(theta) * cos(phi);
		vRandNum[3 * i + 1] = radius * sin(theta) * sin(phi);
		vRandNum[3 * i + 2] = radius * cos(theta);
	}

	ITexture *pRandNumTex = renderer->CreateTexture(RGB, RAND_WIDTH, RAND_WIDTH, RGB, PIXEL_UNSIGNED_BYTE, (void*)vRandNum);

	IGameObject *indirectCamera = cameraNode->AddGameObject();
	IGameObject *indirectObject = pRootNode->AddGameObject();
	CCameraComponent *pIndirectCamera = indirectCamera->AddComponent<CCameraComponent>();
	//pIndirectCamera->Initialize(renderer, CCameraComponent::Ortho, 1000.f, 1000.f / aspect, -10000.f, 10000.f);
    pIndirectCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 10000.f);
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
        
        indirectMaterial->SetProperty("vplViewMatrix", (void *)vplCamera->GetViewMatirx().m, sizeof(CMatrix4));
        indirectMaterial->SetProperty("vplProjMatrix", (void *)vplCamera->GetProjectMatirx().m, sizeof(CMatrix4));
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

	/*
	//blur
	IGameObject *gaussianHObject = pRootNode->AddGameObject();
    CMeshRendererComponent *pGaussianHRenderer = gaussianHObject->AddComponent<CMeshRendererComponent>();
    gaussianMesh = new CMesh();
     
    gaussianMesh ->SetPositions(quadVertices, sizeof(quadVertices));
    gaussianMesh ->SetUVs(quadTexCoords, sizeof(quadTexCoords));
    gaussianMesh ->SetIndices(quadIndices, sizeof(quadIndices));
    
    gaussianHMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/gaussianblur.mat.xml", EResourceType::Material);
	if (indirectTarget)
	{
		uint textureUnit = 0;
		gaussianHMaterial->SetProperty("textureColor", &textureUnit, sizeof(textureUnit));
		static const int MAX_SAMPLER_COUNT = 15;
		float m_kernel[MAX_SAMPLER_COUNT * 4];
		float scale = 0.001f;
		float c = 0.f;
		//float seg = 0.1f;
		//float seg_2 = seg * seg;
		for (auto d = 0; d < MAX_SAMPLER_COUNT; ++d)
		{
			float e = -1 + 2 * d / (MAX_SAMPLER_COUNT - 1.0f);
			float f = e;
			//f = expf(-0.5f * f * f / seg_2) / (2.f * PI * seg_2);
			f = expf(-0.5f * f * f / 1.f) / 2.50662827463f;
			c += f;
			m_kernel[4 * d + 0] = e * scale;
			m_kernel[4 * d + 1] = 0;
			m_kernel[4 * d + 2] = f;
			m_kernel[4 * d + 3] = 0;
		}
		for (auto d = 0; d < MAX_SAMPLER_COUNT; ++d)
			m_kernel[4 * d + 2] /= c;

		gaussianHMaterial->SetProperty("uKernel", m_kernel, sizeof(m_kernel));

        pGaussianHRenderer->Initialize(renderer, pIndirectCamera->GetFlag(), gaussianMesh, gaussianHMaterial);
		pGaussianHRenderer->SetTexture(0, indirectTarget->GetBindTexture(0));
	}
    
	IGameObject *gaussianVObject = pRootNode->AddGameObject();
    CMeshRendererComponent *pGaussianVRenderer = gaussianVObject->AddComponent<CMeshRendererComponent>();
        
    gaussianVMaterial = (IMaterial *)resourceMgr->LoadResource("resource/material/gaussianblur.mat.xml", EResourceType::Material);
	if (indirectTarget)
	{
		uint textureUnit = 0;
		gaussianVMaterial->SetProperty("textureColor", &textureUnit, sizeof(textureUnit));
		static const int MAX_SAMPLER_COUNT = 15;
		float m_kernel[MAX_SAMPLER_COUNT * 4];
		float scale = 0.001f;
		float c = 0.f;
		//float seg = 0.1f;
		//float seg_2 = seg * seg;
		float ratio = 1.f * esContext->width / esContext->height;
		for (auto d = 0; d < MAX_SAMPLER_COUNT; ++d)
		{
			float e = -1 + 2 * d / (MAX_SAMPLER_COUNT - 1.0f);
			float f = e;
			//f = expf(-0.5f * f * f / seg_2) / (2.f * PI * seg_2);
			f = expf(-0.5f * f * f / 1.f) / 2.50662827463f;
			c += f;
			m_kernel[4 * d + 0] = 0;
			m_kernel[4 * d + 1] = e * scale * ratio;
			m_kernel[4 * d + 2] = f;
			m_kernel[4 * d + 3] = 0;
		}
		for (auto d = 0; d < MAX_SAMPLER_COUNT; ++d)
			m_kernel[4 * d + 2] /= c;
		gaussianVMaterial->SetProperty("uKernel", m_kernel, sizeof(m_kernel));

        pGaussianVRenderer->Initialize(renderer, pIndirectCamera->GetFlag(), gaussianMesh, gaussianVMaterial);
		pGaussianVRenderer->SetTexture(0, indirectTarget->GetBindTexture(0));
	}
	*/
    
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
		float lightSwitch = 1.0f;
        deferredMaterial->SetProperty("indirectLightSwitch", &lightSwitch, sizeof(float));
        deferredMaterial->SetProperty("directLightSwitch", &lightSwitch, sizeof(float));
		lightSwitch = 0.0f;
        deferredMaterial->SetProperty("shadowSwitch", &lightSwitch, sizeof(float));
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
		ISceneNode *camNode = cameraNode;
		CVector3 camPos = camNode->GetPosition();
		CVector3 dir(0, 0, -1);
		CVector3 right(1, 0, 0);
		CVector3 up(0, 1, 0);
		CMatrix4 transform = camNode->GetAbsluateTransform();
		transform.SetTranslation(CVector3(0, 0, 0));
		transform.TransformVect(dir);
		transform.TransformVect(right);
		transform.TransformVect(up);
		dir.normalize();
		right.normalize();
		up.normalize();


		CVector3 rotation = camNode->GetRotation();
		static float indirectLightSwitch = 1.0;
		static float directLightSwitch = 1.0;
		static float shadowSwitch = 0.0;

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

		case '1':
			indirectLightSwitch = 1.0f - indirectLightSwitch;
			pDeferredRenderer->GetShaderProgram()->SetUniform("indirectLightSwitch", &indirectLightSwitch);
			break;
		case '2':
			directLightSwitch = 1.0f - directLightSwitch;
			pDeferredRenderer->GetShaderProgram()->SetUniform("directLightSwitch", &directLightSwitch);
			break;
		case '3':
			shadowSwitch = 1.0f - shadowSwitch;
			pDeferredRenderer->GetShaderProgram()->SetUniform("shadowSwitch", &shadowSwitch);
			break;
		case 'P':
		case 'p':
			LogInfo("FPS:%d\n", mc->GetFPS());
			break;
		}
		sphereNode->SetPosition(spherePosition);
		camNode->SetPosition(camPos);
		camNode->SetRotation(rotation);
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
