#include "magic.h"
#include "scene/CGameObject.h"
#include "component/CCamera.h"

#include <stdio.h>

using namespace magic;
int main(int argc, char *argv[])
{
    IMagic *mc = GetMagic();
    printf("Start initalizing Engine ... \n");
    mc->InitEngine();
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    CSceneManager *pSceneMgr = mc->GetSceneManager();
    CScene *pScene = pSceneMgr->LoadScene("Test.scene");
    CGameObject *go = pScene->AddGameObject<CGameObject>();
    go->AddComponent<CCamera>();
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