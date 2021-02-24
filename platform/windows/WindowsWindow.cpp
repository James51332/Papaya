#include "WindowsWindow.h"
#include "WindowsInputCode.h"

#include "main/renderer/Context.h"

#include "main/events/AppEvent.h"
#include "main/events/KeyEvent.h"
#include "main/events/MouseEvent.h"
#include "main/events/EventQueue.h"

#include <windowsx.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        // Event fired when the window is created
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        (void)BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_LBUTTONDOWN:
    {
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MousePressEvent>(Papaya::MouseLeft));
        break;
    }

    case WM_LBUTTONUP:
    {
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseReleaseEvent>(Papaya::MouseLeft));
        break;
    }

    case WM_RBUTTONDOWN:
    {
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MousePressEvent>(Papaya::MouseRight));
        break;
    }

    case WM_RBUTTONUP:
    {
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseReleaseEvent>(Papaya::MouseRight));
        break;
    }

    case WM_MBUTTONDOWN:
    {
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MousePressEvent>(Papaya::MouseMiddle));
        break;
    }

    case WM_MBUTTONUP:
    {
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseReleaseEvent>(Papaya::MouseMiddle));
        break;
    }

    case WM_XBUTTONDOWN:
    {
        int fwButton = GET_XBUTTON_WPARAM(wParam);
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MousePressEvent>(fwButton == 1 ? Papaya::Mouse4 : Papaya::Mouse5));
        break;
    }

    case WM_XBUTTONUP:
    {
        int fwButton = GET_XBUTTON_WPARAM(wParam);
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseReleaseEvent>(fwButton == 1 ? Papaya::Mouse4 : Papaya::Mouse5));
        break;
    }

    case WM_MOUSEHWHEEL:
    {
        int scroll = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseScrollEvent>(scroll, 0));
        break;
    }

    case WM_MOUSEWHEEL:
    {
        int scroll = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseScrollEvent>(0, scroll));
        break;
    }

    case WM_MOUSEMOVE:
    {
        float xPos = static_cast<float>(GET_X_LPARAM(lParam));
        float yPos = static_cast<float>(GET_Y_LPARAM(lParam));
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseMoveEvent>(xPos, yPos));
        break;
    }

    case WM_KEYDOWN:
    {
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::KeyPressEvent>(Papaya::Win32KeyCodeToPapayaKeyCode(static_cast<int>(wParam))));
        break;
    }

    case WM_KEYUP:
    {
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::KeyReleaseEvent>(Papaya::Win32KeyCodeToPapayaKeyCode(static_cast<int>(wParam))));
        break;
    }

    case WM_DESTROY:
    {
        // Event fired when the window is destroyed
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowCloseEvent>());
        break;
    }

    case WM_SIZING:
    {
        RECT frame = *(RECT *)lParam;
        float width = static_cast<float>(frame.right - frame.left);
        float height = static_cast<float>(frame.bottom - frame.top);
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowResizeEvent>(width, height));
    }

    case WM_SIZE:
    {
        float width = static_cast<float>(LOWORD(lParam));
        float height = static_cast<float>(HIWORD(lParam));
        Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowResizeEvent>(width, height));
    }

    default:
        return ::DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

namespace Papaya
{
    bool WindowsWindow::s_KeyCodesInitialized = false;

    WindowsWindow::WindowsWindow(const WindowAttribs &attribs)
    {
        if (!s_KeyCodesInitialized)
        {
            InitWin32InputCodes();
            s_KeyCodesInitialized = true;
        }

        m_Attribs = attribs;

        WNDCLASSEX wc;
        wc.cbClsExtra = 0;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = 0;
        wc.hbrBackground = NULL;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        wc.hInstance = NULL;
        wc.lpszClassName = "PapayaWindow";
        wc.lpszMenuName = "";
        wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = &WndProc;

        bool registered = ::RegisterClassEx(&wc);
        PAPAYA_ASSERT(registered, "Failed to Register Window Class!");

        DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

        if (attribs.Resizable)
            style |= WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

        RECT size;
        GetClientRect(GetDesktopWindow(), &size);
        size.left = (size.right - attribs.Width) / 2;
        size.top = (size.bottom - attribs.Height) / 2;
        size.right = size.left + attribs.Width;  // HACK: Add 4 px because Windows is weird. (This might be my fault.)
        size.bottom = size.top + attribs.Height; // TODO: Look here if window isn't sizing correctly

        AdjustWindowRectEx(&size, style, FALSE, 0);

        m_Hwnd = ::CreateWindowEx(NULL,
                                  "PapayaWindow",
                                  attribs.Title.Raw(),
                                  style,
                                  size.left,
                                  size.top,
                                  size.right - size.left,
                                  size.bottom - size.top,
                                  NULL,
                                  NULL,
                                  NULL,
                                  this);

        PAPAYA_ASSERT(m_Hwnd, "Failed to Create Window!");
    }

    WindowsWindow::~WindowsWindow()
    {
    }

    void WindowsWindow::Show()
    {
        ::ShowWindow(m_Hwnd, SW_SHOW);
    }

    void WindowsWindow::Hide()
    {
        ::ShowWindow(m_Hwnd, SW_HIDE);
    }

    void WindowsWindow::Close()
    {
        ::CloseWindow(m_Hwnd);
    }

    void WindowsWindow::OnUpdate()
    {
        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetContext(const Ref<Context> &context)
    {
        m_Context = context;
    }

} // namespace Papaya
