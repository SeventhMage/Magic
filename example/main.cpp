//#include "HelloTriangle.h"
#include "GI/Source/CGI.h"

#include <stdio.h>
//#include <Windows.h>

using namespace magic;
int main(int argc, char *argv[])
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SRenderContext content;

    //HelloTriangle triangle(&content);
    CGI gi;
    gi.Init(&content);
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
	}

    return 0;
}