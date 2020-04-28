// The MIT License (MIT)
//
// Copyright (c) 2013 Dan Ginsburg, Budirijanto Purnomo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//
// Book:      OpenGL(R) ES 3.0 Programming Guide, 2nd Edition
// Authors:   Dan Ginsburg, Budirijanto Purnomo, Dave Shreiner, Aaftab Munshi
// ISBN-10:   0-321-93388-5
// ISBN-13:   978-0-321-93388-1
// Publisher: Addison-Wesley Professional
// URLs:      http://www.opengles-book.com
//            http://my.safaribooksonline.com/book/animation-and-3d/9780133440133
//
// Hello_Triangle.c
//
//    This is a simple example that draws a single triangle with
//    a minimal vertex/fragment shader.  The purpose of this
//    example is to demonstrate the basic concepts of
//    OpenGL ES 3.0 rendering.
#include "magic.h"
#include "scene/CGameObject.h"
#include "resource/CMesh.h"
#include "resource/CMaterial.h"
#include "resource/CShader.h"
#include "resource/IImage.h"
#include "ERender.h"
#include "component/CCameraComponent.h"
#include "component/CMeshRendererComponent.h"

#include <stdio.h>

#include <OpenGLES/ES3/gl.h>

using namespace magic;

IMagic *mc = nullptr;
IRenderer *renderer;
ISceneManager *pSceneMgr = nullptr;
IMesh *mesh = nullptr;
IShader *vertShader;
IShader *fragShader;
IMaterial *material;
//IRenderTarget *renderTarget;

//需要手动控件销毁顺序，保证在引擎销毁前删除
CGameObject *camera = new CGameObject();
CGameObject *triangle = new CGameObject();

float vertices[][3] = {  0.0f,  0.5f, 0.0f,
                         -0.5f, -0.5f, 0.0f,
                         0.5f, -0.5f, 0.0f
                      };
float colors[][4] = {
    1.0f, 0.8f, 0.8f, 1.0f,
    0.8f, 1.0f, 0.8f, 1.0f,
    .8f, .8f, 1.0f, 1.0f,
};

float texCoords[][2] = {
    0.5f, 1.f,
    0.f, 0.f,
    1.f, 0.f,
};

float normals[][3] = {
    0.f, 0.f, 1.f,
    0.f, 0.f, 1.f,
    0.f, 0.f, 1.f,
};

unsigned short indices[] = {0, 1, 2};

char vShaderStr[] =
 "#version 300 es                          \n"
 "layout(location = 0) in vec3 vPosition;  \n"
"layout(location = 1) in vec2 vTexCoord;  \n"
 "layout(location = 2) in vec4 vColor;     \n"
 "out vec4 vOutColor;                      \n"
 "out vec2 vTex;                           \n"
 "uniform mat4 vpMatrix;                   \n"
 "uniform mat4 mMatrix;                    \n"
 "void main()                              \n"
 "{                                        \n"
 "   vOutColor = vColor;                   \n"
 "   vTex = vTexCoord;                     \n"
 "   gl_Position = vpMatrix * mMatrix * vec4(vPosition, 1.0);   \n"
 "}                                        \n";

char fShaderStr[] =
 "#version 300 es                              \n"
 "precision mediump float;                     \n"
 "uniform sampler2D textureUnit;               \n"
 "uniform vec4 color;               \n"
 "in vec4 vOutColor;                           \n"
 "in vec2 vTex;                                \n"
 "out vec4 fragColor;                          \n"
 "void main()                                  \n"
 "{                                            \n"
 "   fragColor = color * vOutColor * texture(textureUnit, vTex);   \n"
 "}                                            \n";

float ambientLightColor[] = {0.2f, 0.2f, 0.2f};
float directionalLightDir[] = {1.f, 1.f, 1.f};
float directionalLightColor[] = {0.8f, 0.8f, 0.8f};
float specCoefficient = 10;

CVector3 pos;
float flag = 0.02f;
float rot = 0;

void update()
{
    mc->Run();
    //camera.GetSceneNode()->SetPosition(pos);
    if (pos.x > 0.6f || pos.x < -0.6f)
        flag = -flag;
    pos.x += flag;
    
    triangle->GetSceneNode()->SetRotation(CVector3(0, rot, 0));
    
    //triangle.GetSceneNode()->SetPosition(pos);
    rot += flag;
    //printf("Delta:%lu\n", mc->GetTime()->GetDeltaTime());
}

void shutdown()
{
    printf("Application end.\n\n");

    printf("Cleaning ... \n");
    pSceneMgr->UnloadScene();
    delete material;
    delete fragShader;
    delete vertShader;
    delete mesh;
    delete camera;
    delete triangle;
    //delete renderTarget;
    Clean();
    printf("Finish clean.\n\n");
}

int esMain ( SRenderContext *esContext )
{
    printf("Start initalizing Engine ... \n");
    mc = CreateMagic(esContext, "Triangle", 1280, 960);
    mc->SetFPS(60);
    esContext->updateFunc = &update;
    esContext->shutdownFunc = &shutdown;
    renderer = mc->GetRenderer();
    IResourceManager *resourceMgr = mc->GetResourceManager();
    //renderTarget = renderer->CreateRenderTarget(800, 600);
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    pSceneMgr = mc->GetSceneManager();
    IScene *pScene = pSceneMgr->LoadScene();
    ISceneNode *pRootNode = pScene->GetRootNode();
    ISceneNode *cameraNode = pRootNode->CreateChildNode();
    ISceneNode *triangleNode = pRootNode->CreateChildNode();
    camera->SetSceneNode(cameraNode);
    triangle->SetSceneNode(triangleNode);
    cameraNode->SetPosition(CVector3(0, 0, 2));
    CCameraComponent *pCamera = camera->AddComponent<CCameraComponent>();
    float aspect = 1.f * esContext->width / esContext->height;
    //pCamera->Initialize(renderer, CCameraComponent::Ortho, 2.f, 2.f / aspect, -100.f, 100.f);
    pCamera->Initialize(renderer, CCameraComponent::Projection, PI / 3, aspect, 1.f, 1000.f);
    pCamera->SetClearColor(0.5, 0.5, 0.5, 1);
    pCamera->SetClearBit(MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT | MAGIC_COLOR_BUFFER_BIT);
    //pCamera->SetRenderTarget(renderTarget);
    
    CMeshRendererComponent *pMeshRenderer = triangle->AddComponent<CMeshRendererComponent>();
    
    mesh = new CMesh();
    
    mesh->SetPositions(vertices, sizeof(vertices));
    mesh->SetColors(colors, sizeof(colors));
    mesh->SetUVs(texCoords, sizeof(texCoords));
    mesh->SetIndices(indices, sizeof(indices));
    mesh->SetNormals(normals, sizeof(normals));

    //vertShader = new CShader(EShaderType::Vertex, vShaderStr, sizeof(vShaderStr));
    //fragShader = new CShader(EShaderType::Fragment, fShaderStr, sizeof(fShaderStr));
    vertShader = (CShader *)resourceMgr->LoadResource("common.vert", EResourceType::Shader);
    fragShader = (CShader *)resourceMgr->LoadResource("common.frag", EResourceType::Shader);
    material = new CMaterial();
    material->SetShader(vertShader->GetShaderType(), vertShader);
    material->SetShader(fragShader->GetShaderType(), fragShader);
    float colorProperty[] = {0.5f, 0.5f, 0.5f, 1.0f};
    material->SetProperty("color", colorProperty, sizeof(colorProperty));
    material->SetProperty("ambientLightColor", ambientLightColor, sizeof(ambientLightColor));
    material->SetProperty("directionalLightDir", directionalLightDir, sizeof(directionalLightDir));
    material->SetProperty("directionalLightColor", directionalLightColor, sizeof(directionalLightColor));
    material->SetProperty("specCoefficient", &specCoefficient, sizeof(specCoefficient));
    CMatrix4 transform = camera->GetSceneNode()->GetAbsluateTransform();
    transform.SetTranslation(CVector3(0, 0, 0));
    CVector3 viewDir(0, 0, 1.f);
    transform.TransformVect(viewDir);
    material->SetProperty("viewDir", viewDir.v, sizeof(viewDir));
    IImage *pImage = (IImage *)resourceMgr->LoadResource("crate.tga", EResourceType::Image);
    
    pMeshRenderer->Initialize(mc->GetRenderer(), mesh, material, pImage);
    resourceMgr->UnloadResource(pImage);
    
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");

    return 1;
}
