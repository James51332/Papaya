#ifndef CocoaInputCode_h
#define CocoaInputCode_h

#include "main/core/KeyCode.h"
#include "main/core/MouseCode.h"

namespace Papaya
{

void InitCocoaInputCodes();

Papaya::KeyCode CocoaKeyCodeToPapayaKeyCode(unsigned int keyCode);
Papaya::MouseCode CocoaMouseCodeToPapayaMouseCode(unsigned int mouseCode);

} // namespace Papaya

#endif /* end of include guard: CocoaInputCode_h */