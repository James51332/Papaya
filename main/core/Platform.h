#ifndef Platform_h
#define Platform_h

#include "main/utils/Memory.h"
#include "main/utils/String.h"

namespace Papaya
{

  class Platform
  {
  public:
    virtual ~Platform();

    static void OnInit();
    static void OnUpdate();
    static void OnTerminate();

    // returns time in seconds
    static double GetSysTime();
    static String LoadFile(const String& path);

  protected:
    static Scope<Platform> Create();
    Platform();

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Terminate() = 0;
    virtual double SysTime() = 0;

  private:
    static Scope<Platform> s_Instance;
  };

} // namespace Papaya

#endif /* end of include guard: Platform_h */