#include "../include/magic.h"

#include "../include/scene/CGameObject.h"
#include "../include/component/CCamera.h"

#include <stdio.h>

using namespace magic;
int main(int argc, char *argv[])
{
    IMagic *mc = GetMagic();
    printf("Start initalizing Engine ... \n");
    mc->InitEngine();
    printf("Finished initalizing Engine.\n\n");

    CGameObject go;
    go.AddComponent<CCamera>();

    printf("Loading scene ... \n");
    ISceneManager *pSceneMgr = mc->GetSceneManager();
    IScene *pScene = pSceneMgr->LoadScene("Test.scene");
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");
    mc->StartApplication();
    printf("Application end.\n\n");

    printf("Cleaning ... \n");
    pSceneMgr->UnloadScene(pScene);
    Clean();
    printf("Finish clean.\n\n");
    getchar();
    return 0;
}