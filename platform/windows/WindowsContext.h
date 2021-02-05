#ifndef WindowsContext_h
#define WindowsContext_h

#include "main/renderer/Context.h"

namespace Papaya
{

////////////////////////////////////////////
///// WindowsContext ///////////////////////
////////////////////////////////////////////

class WindowsContext : public Context
{
public:
    static Ref<Context> Create(const Scope<Window>& window, RenderApi api);
    virtual ~WindowsContext();
    
    virtual void SwapBuffers() = 0;
};

////////////////////////////////////////////
///// WindowsOpenGLContext /////////////////
////////////////////////////////////////////

class WindowsOpenGLContext : public WindowsContext
{
public:
    WindowsOpenGLContext(const Scope<Window>& window);
    virtual ~WindowsOpenGLContext();

    void SwapBuffers();
};

} // namespace Papaya


#endif /* end of include guard: WindowsContext_h */