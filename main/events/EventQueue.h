#ifndef EventQueue_h
#define EventQueue_h

#include <list>

#include "main/events/Event.h"

#include "main/utils/Memory.h"

namespace Papaya
{

  class EventQueue
  {
  public:
    static void PushEvent(Scope<Event> event);

    // Pops the last element on the EventQueue. Undefined Behavior if list is empty
    static Scope<Event> PopEvent();
    static bool Empty();

  private:
    static std::list<Scope<Event>> s_Queue;
  };

} // namespace Papaya

#endif /* end of include guard: EventQueue_h */