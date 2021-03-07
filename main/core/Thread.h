#pragma once

#include "main/utils/Memory.h"

#include <thread>
#include <functional>

namespace Papaya
{

enum class TaskPriority
{
  Normal = 0,
  Important,
  Critical
}; // TODO: Thread Priorities (Will Require Native Threading Library)

template <typename T>
using Task = std::function<T>;

// Wrapper around std::thread. Eventually, this will
// be written using native api calls to implement thread priorities
class Thread
{
public:

  template<typename T>
  Thread(T& job)
    : m_Thread(job) {
  
  }

  void Join() {
    m_Thread.join();
  }

  bool Joinable() {
    return m_Thread.joinable();
  }

private:
  std::thread m_Thread;
};

} // namespace Papaya