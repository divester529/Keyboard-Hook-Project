#include <Windows.h>
#include <stdio.h>
#include "KeyboardHook.hpp"

/*LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int args)
{
    KeyboardHook* instance = new KeyboardHook();

    instance->initHook();
    
    if(!instance->createWindow(args))
        {
            puts("Error");
            return 0;
        }

    instance->run();

    return 1;
}