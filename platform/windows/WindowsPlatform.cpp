#include "WindowsPlatform.h"

#include <windows.h>

namespace Papaya
{
    
WindowsPlatform::WindowsPlatform() {
    ::PostQuitMessage(0);
}

WindowsPlatform::~WindowsPlatform() {

}

void WindowsPlatform::Init() {

}

void WindowsPlatform::Update() {
    MSG msg;

    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void WindowsPlatform::Terminate() {

}

} // namespace Papaya
