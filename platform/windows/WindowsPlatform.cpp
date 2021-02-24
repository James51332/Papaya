#include "WindowsPlatform.h"

#include <windows.h>

namespace Papaya
{

    WindowsPlatform::WindowsPlatform()
    {
        ::PostQuitMessage(0);
    }

    WindowsPlatform::~WindowsPlatform()
    {
    }

    void WindowsPlatform::Init()
    {
        if (!QueryPerformanceFrequency((LARGE_INTEGER *) &m_TimerFrequency))
            m_TimerFrequency = 1000;

        QueryPerformanceCounter((LARGE_INTEGER*)&m_TimerOffset);
    }

    void WindowsPlatform::Update()
    {
        MSG msg;

        while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void WindowsPlatform::Terminate()
    {
    }

    double WindowsPlatform::SysTime()
    {
        uint64_t value;
        QueryPerformanceCounter((LARGE_INTEGER*)&value);

        return static_cast<double>(value - m_TimerOffset) / static_cast<double>(m_TimerFrequency);

    }

} // namespace Papaya
