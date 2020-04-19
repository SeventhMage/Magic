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

CGameObject camera;
CGameObject triangle;

void update()
{
    mc->Run();
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
    Clean();
    printf("Finish clean.\n\n");
}

int esMain ( SRenderContext *esContext )
{
    printf("Start initalizing Engine ... \n");
    mc = CreateMagic(esContext, "Triangle", 1280, 960);
    esContext->updateFunc = &update;
    esContext->shutdownFunc = &shutdown;
    renderer = mc->GetRenderer();
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    pSceneMgr = mc->GetSceneManager();
    IScene *pScene = pSceneMgr->LoadScene();
    IGameObject *go = pScene->GetRootGameObject();
    
    CCameraComponent *pCamera = camera.AddComponent<CCameraComponent>();
    pCamera->Initialize(renderer, CCameraComponent::Projection);
    pCamera->SetClearColor(0.5, 0.5, 0.5, 1);
    pCamera->SetClearBit(MAGIC_DEPTH_BUFFER_BIT | MAGIC_STENCIL_BUFFER_BIT | MAGIC_COLOR_BUFFER_BIT);
    go->GetSceneNode()->AddChild(camera.GetSceneNode());
    
    CMeshRendererComponent *pMeshRenderer = triangle.AddComponent<CMeshRendererComponent>();
    go->GetSceneNode()->AddChild(triangle.GetSceneNode());
    mesh = new CMesh();

    float vertices[][3] = {  0.0f,  0.5f, 0.0f,
                             -0.5f, -0.5f, 0.0f,
                             0.5f, -0.5f, 0.0f
                          };
    float colors[][4] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };
    unsigned short indices[] = {0, 1, 2};
    mesh->SetPositions(vertices, sizeof(vertices));
    mesh->SetColors(colors, sizeof(colors));
    //mesh->SetIndices(indices, sizeof(indices));
    char vShaderStr[] =
     "#version 300 es                          \n"
     "layout(location = 0) in vec3 vPosition;  \n"
     "layout(location = 1) in vec4 vColor;     \n"
     "out vec4 vOutColor;                      \n"
     "void main()                              \n"
     "{                                        \n"
     "   vOutColor = vColor;                   \n"
     "   gl_Position = vec4(vPosition, 1.0);   \n"
     "}                                        \n";

    char fShaderStr[] =
     "#version 300 es                              \n"
     "precision mediump float;                     \n"
     "in vec4 vOutColor;                           \n"
     "out vec4 fragColor;                          \n"
     "void main()                                  \n"
     "{                                            \n"
     "   fragColor = vOutColor;                    \n"
     "}                                            \n";
    vertShader = new CShader(EShaderType::Vertex, vShaderStr, sizeof(vShaderStr));
    fragShader = new CShader(EShaderType::Fragment, fShaderStr, sizeof(fShaderStr));
    material = new CMaterial();
    material->AddAttribute("vPosition");
    material->AddAttribute("vColor");
    material->SetShader(vertShader->GetShaderType(), vertShader);
    material->SetShader(fragShader->GetShaderType(), fragShader);
    pMeshRenderer->Initialize(mc->GetRenderer(), material, mesh);
    go->GetSceneNode()->AddChild(triangle.GetSceneNode());
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");

    return 1;
}
