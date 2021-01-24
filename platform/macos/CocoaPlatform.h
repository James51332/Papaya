#ifndef CocoaPlatform_h
#define CocoaPlatform_h

#include "main/core/Platform.h"

namespace Papaya
{

class CocoaPlatform : public Platform {
public:
  CocoaPlatform();
  virtual ~CocoaPlatform();

  void Init();
  void Update();
  void Terminate();

private:
  void* m_Application;
};

} // namespace Papaya


#endif /* end of include guard: CocoaPlatform_h */