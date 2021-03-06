#pragma once

#include "main/core/Platform.h"

namespace Papaya
{

  class WindowsPlatform : public Platform
  {
  public:
    WindowsPlatform();
    virtual ~WindowsPlatform();

    void Init();
    void Update();
    void Terminate();
    double SysTime();

  private:
    uint64_t m_TimerOffset;
    uint64_t m_TimerFrequency;
  };

} // namespace Papaya