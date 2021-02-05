#include "WindowsContext.h"

#include "main/core/Window.h"
#include "main/core/Log.h"

#include <Windows.h>

namespace Papaya
{

////////////////////////////////////////////
///// WindowsContext ///////////////////////
////////////////////////////////////////////

Ref<Context> WindowsContext::Create(const Scope<Window>& window, RenderApi api)
{
    switch (api)
    {
        case RenderApi::OpenGL: {
            return CreateRef<WindowsOpenGLContext>(Move(window));
        }

        default: break;
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

WindowsOpenGLContext::WindowsOpenGLContext(const Scope<Window>& window)
{

}

WindowsOpenGLContext::~WindowsOpenGLContext()
{

}

void WindowsOpenGLContext::SwapBuffers()
{

}

} // namespace Papaya
