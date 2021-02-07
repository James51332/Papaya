#ifndef CocoaContext_h
#define CocoaContext_h

#include "main/renderer/Context.h"

namespace Papaya
{

////////////////////////////////////////////
///// CocoaContext /////////////////////////
////////////////////////////////////////////

class CocoaWindow;

class CocoaContext : public Context
{
  friend class CocoaWindow;
public:
  static Ref<Context> Create(const Scope<Window>& window, RenderApi api);
  virtual ~CocoaContext();

  virtual void SwapBuffers() = 0;

protected:
  void* m_View;

  static bool s_KeyCodesInitialized;
};

////////////////////////////////////////////
///// CocoaOpenGLContext ///////////////////
////////////////////////////////////////////

class CocoaOpenGLContext : public CocoaContext
{
public:
  CocoaOpenGLContext(const Scope<Window>& window);
  virtual ~CocoaOpenGLContext();

  void SwapBuffers();

private:
  void* m_Context;
};

} // namespace Papaya

#endif /* end of include guard: CocoaContext_h */