#include "WindowsWindow.h"

#include "main/renderer/Context.h"

#include "main/events/AppEvent.h"
#include "main/events/EventQueue.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        // Event fired when the window is created
        break;
    }

    case WM_DESTROY:
    {
        // Event fired when the window is destroyed
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowCloseEvent>());
        break;
    }

    default:
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return 0;
}

namespace Papaya
{
    WindowsWindow::WindowsWindow(const WindowAttribs &attribs) {
        m_Attribs = attribs;

        WNDCLASSEX wc;
        wc.cbClsExtra = 0;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = 0;
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        wc.hInstance = NULL;
        wc.lpszClassName = "PapayaWindow";
        wc.lpszMenuName = "";
        wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = &WndProc;

        if (!::RegisterClassEx(&wc))
            PAPAYA_ASSERT(false, "Failed to Register Window Class!");

        DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

        if (attribs.Resizable)
            style |= WS_THICKFRAME;

        // TODO: Disable/Enable Resizability on Windows
        m_Hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, 
                                  "PapayaWindow", 
                                  attribs.Title.Raw(), 
                                  style,
                                  CW_USEDEFAULT, 
                                  CW_USEDEFAULT, 
                                  attribs.Width, 
                                  attribs.Height,
                                  NULL, 
                                  NULL, 
                                  NULL, 
                                  this);

        if (!m_Hwnd)
            PAPAYA_ASSERT(false, "Failed to Create Window!");
    }

    WindowsWindow::~WindowsWindow() {

    }

    void WindowsWindow::Show() {
        ::ShowWindow(m_Hwnd, SW_SHOW);
        ::UpdateWindow(m_Hwnd);
    }

    void WindowsWindow::Hide() {

    }

    void WindowsWindow::Close() {

    }

    void WindowsWindow::OnUpdate()
    {
       // m_Context->SwapBuffers();
    }

    void WindowsWindow::SetContext(const Ref<Context> &context)
    {

    }

} // namespace Papaya
