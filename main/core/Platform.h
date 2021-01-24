#ifndef Platform_h
#define Platform_h

#include "main/core/Memory.h"

namespace Papaya
{

class Platform {
public:
  virtual ~Platform();

  static void OnInit();
  static void OnUpdate();
  static void OnTerminate();

protected:
  static Scope<Platform> Create();
  Platform();

  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void Terminate() = 0;

private:
  static Scope<Platform> s_Instance;
};

} // namespace Papaya


#endif /* end of include guard: Platform_h */