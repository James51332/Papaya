#ifndef EventQueue_h
#define EventQueue_h

#include <list>

#include "main/events/Event.h"

#include "main/core/Memory.h"

namespace Papaya
{

class EventQueue {
public:
  static void PushEvent(Scope<Event> event);

  // Pops the last element on the EventQueue. It is stored in a buffer and only valid until the next event is popped.
  static Scope<Event> PopEvent();
  static bool Empty();
private:
  static std::list<Scope<Event>> s_Queue;
};

} // namespace Papaya


#endif /* end of include guard: EventQueue_h */