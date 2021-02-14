#ifndef WindowsInputCode_h
#define WindowsInputCode_h

#include "main/core/KeyCode.h"
#include "main/core/MouseCode.h"

namespace Papaya
{

  void InitWin32InputCodes();

  Papaya::KeyCode Win32KeyCodeToPapayaKeyCode(unsigned int keyCode);

} // namespace Papaya

#endif /* end of include guard: WindowsInputCode_h */