#pragma once

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
    static Ref<Context> Create(const Scope<Window> &window, RenderApi::API api);
    virtual ~Context();

    RenderApi::API GetApi() const { return m_Api; }

    virtual void SwapBuffers() = 0;

  protected:
    RenderApi::API m_Api;

    static bool s_OpenGLInitialized;
  };

} // namespace Papaya