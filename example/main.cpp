#include "magic.h"
#include "scene/CGameObject.h"
#include "resource/CMesh.h"
#include "resource/CMaterial.h"
#include "resource/CShader.h"
#include "component/CCameraComponent.h"
#include "component/CMeshRendererComponent.h"

#include <stdio.h>

using namespace magic;
int main(int argc, char *argv[])
{
    SRenderContent content;
    printf("Start initalizing Engine ... \n");
    IMagic *mc = CreateMagic(&content, "Test", 1280, 960);
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    ISceneManager *pSceneMgr = mc->GetSceneManager();
    IScene *pScene = pSceneMgr->LoadScene();
    IGameObject *go = pScene->GetRootGameObject();
    CGameObject camera;
    camera.AddComponent<CCameraComponent>();
    go->GetSceneNode()->AddChild(camera.GetSceneNode());
    CGameObject triangle;
    CMeshRendererComponent *pMeshRenderer = triangle.AddComponent<CMeshRendererComponent>();
    IMesh *mesh = new CMesh();
    float vertices[] = {
        -1, -1, 0, 1, 0, 0, 1,
        1, -1, 0, 0, 1, 0, 1,
        0, 1, 0, 0, 0, 1, 1};
    short indices[] = {0, 1, 2};
    mesh->SetVertices(vertices, sizeof(vertices));
    mesh->SetVerticesStride(7 * sizeof(float));
    mesh->SetVerticesOffset(0, 0);
    mesh->SetVerticesOffset(1, sizeof(float) * 3);
    mesh->SetVerticesSize(0, 3);
    mesh->SetVerticesSize(1, 4);
    mesh->SetIndices(indices, sizeof(indices));
    char vShaderStr[] =
        "#version 300 es                          \n"
        "layout(location = 0) in vec4 vPosition;  \n"
        "void main()                              \n"
        "{                                        \n"
        "   gl_Position = vPosition;              \n"
        "}                                        \n";

    char fShaderStr[] =
        "#version 300 es                              \n"
        "precision mediump float;                     \n"
        "out vec4 fragColor;                          \n"
        "void main()                                  \n"
        "{                                            \n"
        "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
        "}                                            \n";
    IShader *vertShader = new CShader(EShaderType::Vertex, vShaderStr);
    IShader *fragShader = new CShader(EShaderType::Fragment, fShaderStr);
    IMaterial *material = new CMaterial();
    material->AddAttribute("vPosition");
    material->SetShader(vertShader->GetShaderType(), vertShader);
    material->SetShader(fragShader->GetShaderType(), fragShader);
    pMeshRenderer->Initialize(mc->GetRenderer(), material, mesh);
    go->GetSceneNode()->AddChild(triangle.GetSceneNode());
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");
    mc->Run();
    printf("Application end.\n\n");

    printf("Cleaning ... \n");
    pSceneMgr->UnloadScene();
    delete material;
    delete fragShader;
    delete vertShader;
    Clean();
    printf("Finish clean.\n\n");
    getchar();
    return 0;
}