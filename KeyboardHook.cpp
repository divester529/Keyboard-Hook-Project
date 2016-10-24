#include "KeyboardHook.hpp"
#include <stdio.h>
#include <iostream>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK KeyHookProc(int code, WPARAM wParam, LPARAM lParam);

std::string KeyboardHook::className = "WindowHook GUI";
std::string KeyboardHook::classTitle = "WindowHook GUI";

KeyboardHook::KeyboardHook()
{
    
}

bool KeyboardHook::createWindow(int args)
{
    puts(className.c_str());
    puts(classTitle.c_str());
    // Get instance handle
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    if(hInstance==0)
    {
        puts("Error getting instance handle!");
        return false;
    }

    // Create & register window class
    
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.lpfnWndProc = WindowProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_ASTERISK);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = className.c_str();
    wcex.hIconSm = LoadIcon(hInstance, IDI_ASTERISK);

    if(!RegisterClassEx(&wcex))
    {
        puts("Could not reigster window!");
        return false;
    }

    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                          className.c_str(),
                          classTitle.c_str(),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          500, 100,
                          NULL, NULL,
                          hInstance,
                          NULL);
    if(hWnd==0)
    {
        puts("Could not create window!");
        return false;
    }

    ShowWindow(hWnd, args);
    UpdateWindow(hWnd);

    SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)"Test");
    return true;
}

void KeyboardHook::initHook()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    SetWindowsHookEx(WH_KEYBOARD_LL, KeyHookProc, hInstance, 0);
}

void KeyboardHook::run()
{
    MSG msg;
         
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK KeyHookProc(int code, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* ptrKey = (KBDLLHOOKSTRUCT*)lParam;
    int sysKeyPressed = 0; // If windows key is pressed

    switch(wParam)
    {
        case WM_KEYDOWN:
            if(ptrKey->vkCode==0x5b)
                sysKeyPressed=1;
            if(ptrKey->vkCode=='A')
                system("cmd");
            printf("0x%x\n", ptrKey->vkCode);
        break;
        case WM_KEYUP:
            if(ptrKey->vkCode==0x5b)
                sysKeyPressed=0;

        break;
    }

    return CallNextHookEx(NULL, code, wParam, lParam);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}