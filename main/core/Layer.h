#ifndef Layer_h
#define Layer_h

#include "main/core/Timestep.h"

#include "main/utils/String.h"

#include "main/events/Event.h"

namespace Papaya
{
  
class Layer
{
public:
  Layer(const String& debugName = "Layer");
  virtual ~Layer();

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate(Timestep t) {}
  virtual void OnEvent(const Scope<Event>& event) {}

private:
  String m_DebugName;
};

} // namespace Papaya


#endif /* end of include guard: Layer_h */