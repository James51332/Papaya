#include "EventQueue.h"

namespace Papaya
{

std::list<Scope<Event>> EventQueue::s_Queue;

void EventQueue::PushEvent(Scope<Event> e) {
  s_Queue.emplace_front(Move(e));
}

[[nodiscard]] Scope<Event> EventQueue::PopEvent() {
  auto buffer = Move(s_Queue.back());
  s_Queue.pop_back();
  return buffer;
}

bool EventQueue::Empty() {
  return s_Queue.empty();
}

} // namespace Papaya
