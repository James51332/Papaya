#include "papayapch.h"
#include "WindowsContext.h"

#include "main/core/Window.h"

#include "platform/windows/WindowsWindow.h"

#include <windows.h>
#include <GL/GL.h>
#include <GL/wgl.h>

namespace Papaya
{

  ////////////////////////////////////////////
  ///// WindowsContext ///////////////////////
  ////////////////////////////////////////////

  Ref<Context> WindowsContext::Create(const Scope<Window> &window, RenderApi::API api)
  {
    switch (api)
    {
    case RenderApi::API::OpenGL:
    {
      return CreateRef<WindowsOpenGLContext>(window);
    }

    default:
      break;
    }

    PAPAYA_ASSERT(false, "Please use OpenGL on Windows!");
    return nullptr;
  }

  WindowsContext::~WindowsContext()
  {
  }

  ////////////////////////////////////////////
  ///// WindowsOpenGLContext /////////////////
  ////////////////////////////////////////////

  WindowsOpenGLContext::WindowsOpenGLContext(const Scope<Window> &window)
  {
    WindowsWindow *wnd = static_cast<WindowsWindow *>(window.get());

    HWND hwnd = wnd->m_Hwnd;

    m_Hdc = GetDC(hwnd);
    PAPAYA_ASSERT(m_Hdc, "Failed to acquire device context!");

    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,                       // version
        PFD_DRAW_TO_WINDOW |     // must support windowed
            PFD_SUPPORT_OPENGL | // must support OpenGL
            PFD_DOUBLEBUFFER,    // must support double buffering
        PFD_TYPE_RGBA,           // iPixelType
        32,                      // cColorBits
        0,
        0, // cRedBits, cRedShift
        0,
        0, // cGreenBits, cGreenShift
        0,
        0, // cBlueBits, cBlueShift
        0,
        0,              // cAlphaBits, cAlphaShift
        0,              // cAccumBits
        0,              // cAccumRedBits
        0,              // cAccumGreenBits
        0,              // cAccumBlueBits
        0,              // cAccumAlphaBits
        0,              // cDepthBits
        0,              // cStencilBits
        0,              // cAuxBuffers
        PFD_MAIN_PLANE, // iLayerType
        0,              // bReserved
        0,              // dwLayerMask
        0,              // dwVisibleMask
        0               // dwDamageMask
    };

    int pixelFormat = ChoosePixelFormat(m_Hdc, &pfd);
    PAPAYA_ASSERT(pixelFormat != 0, "Failed to find a suitable PixelFormat!"); // If !(pf != 0) throw error.

    // We can't directly put this in an assert because it will be stripped away in Release/Dist builds.
    bool success = SetPixelFormat(m_Hdc, pixelFormat, &pfd);
    PAPAYA_ASSERT(success, "Failed to set Pixel Format!");

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
    {
      HGLRC hglrc = wglCreateContext(m_Hdc);
      wglMakeCurrent(m_Hdc, hglrc);

      wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

      wglMakeCurrent(NULL, NULL);
      wglDeleteContext(hglrc);
    }

    // TODO: Detect OpenGL Version
    int attribs[] = {WGL_CONTEXT_MAJOR_VERSION_ARB,
                     3,
                     WGL_CONTEXT_MINOR_VERSION_ARB,
                     3,
                     WGL_CONTEXT_PROFILE_MASK_ARB,
                     WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                     WGL_CONTEXT_FLAGS_ARB,
                     WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                     0};

    m_Hglrc = wglCreateContextAttribsARB(m_Hdc, NULL, attribs);
    PAPAYA_ASSERT(m_Hglrc, "Failed to Create OpenGL Context");

    wglMakeCurrent(m_Hdc, m_Hglrc);
  }

  WindowsOpenGLContext::~WindowsOpenGLContext()
  {
  }

  void WindowsOpenGLContext::SwapBuffers()
  {
    ::SwapBuffers(m_Hdc);
  }

} // namespace Papaya
