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
  static Ref<Context> Create(RenderApi api);
  virtual ~CocoaContext();

  virtual void OnUpdate() = 0;

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
  CocoaOpenGLContext();
  virtual ~CocoaOpenGLContext();

  void OnUpdate();

private:
  void* m_Context;
};

} // namespace Papaya

#endif /* end of include guard: CocoaContext_h */