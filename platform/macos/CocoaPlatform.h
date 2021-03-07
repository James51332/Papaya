#pragma once
#include "main/core/Platform.h"

namespace Papaya
{

  class CocoaPlatform : public Platform
  {
  public:
    CocoaPlatform();
    virtual ~CocoaPlatform();

    void Init();
    void Update();
    void Terminate();
    double SysTime();

  private:
    void *m_Application;

    double m_TimerOffset;
    double m_TimerFrequency;
  };

} // namespace Papaya