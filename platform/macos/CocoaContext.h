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

protected:
  void* m_View;
};

////////////////////////////////////////////
///// CocoaOpenGLContext ///////////////////
////////////////////////////////////////////

class CocoaOpenGLContext : public CocoaContext
{
public:
  CocoaOpenGLContext();
  virtual ~CocoaOpenGLContext();

private:
  void* m_Context;
};

} // namespace Papaya

#endif /* end of include guard: CocoaContext_h */