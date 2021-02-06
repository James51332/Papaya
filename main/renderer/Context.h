#ifndef Context_h
#define Context_h

#include "main/utils/Memory.h"

#include "main/renderer/RenderApi.h"

namespace Papaya
{

class Window;

// The Context class creates a context according to platform which creates a context according
// to the RenderApi. This allows for an extensible system with whichever api's we choose.
class Context
{
  friend class Window;
public:
  static Ref<Context> Create(const Scope<Window>& window, RenderApi api);
  virtual ~Context();

  RenderApi GetApi() const { return m_Api; }
  virtual void SwapBuffers() = 0;

protected:
  RenderApi m_Api;

  static bool s_OpenGLInitialized;
};

} // namespace Papaya


#endif /* end of include guard: Context_h */