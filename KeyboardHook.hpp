#ifndef KEYBOARDHOOK_HEADER_INCLUDED
#define KEYBOARDHOOK_HEADER_INCLUDED

#include <windows.h>
#include <string>

class KeyboardHook
{
    public:
    KeyboardHook();
    
    bool createWindow(int args); // Creates window
    void initHook(); // initializes the keyboard hook

    void run();

    private:
    static std::string className;
    static std::string classTitle;

    HWND hWnd;
    WNDCLASSEX wcex;
};

#endif