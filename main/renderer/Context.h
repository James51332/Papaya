#ifndef Context_h
#define Context_h

#include "main/utils/Memory.h"

#include "main/renderer/RenderApi.h"

namespace Papaya
{

// The Context class creates a context according to platform which creates a context according
// to the RenderApi. This allows for an extensible system with whichever api's we choose.
class Context
{
public:
  static Ref<Context> Create(RenderApi api);
  virtual ~Context();

  RenderApi GetApi() const { return m_Api; }

protected:
  RenderApi m_Api;
};

} // namespace Papaya


#endif /* end of include guard: Context_h */