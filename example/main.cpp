#include "magic.h"

#include <stdio.h>
//#include <Windows.h>

using namespace magic;
int main(int argc, char *argv[])
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SRenderContext content;
    printf("Start initalizing Engine ... \n");
    IMagic *mc = CreateMagic(&content, "Test", 1280, 960);
    printf("Finished initalizing Engine.\n\n");

    printf("Loading scene ... \n");
    ISceneManager *pSceneMgr = mc->GetSceneManager();
    IScene *pScene = pSceneMgr->LoadScene();
   
    printf("Finished loading scene. \n\n");

    printf("Start Application ... \n");
    while (true)
    {
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }
        Sleep(100);
    }

    printf("Application end.\n\n");

    printf("Cleaning ... \n");
    pSceneMgr->UnloadScene();
;
    Clean();
    printf("Finish clean.\n\n");
    return 0;
}