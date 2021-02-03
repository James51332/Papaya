#include "CocoaInputCode.h"

#include "main/core/Log.h"

namespace Papaya {

#define COCOA_KEYCODE_SIZE 256
#define COCOA_MOUSECODE_SIZE 10

Papaya::KeyCode CocoaKeyCodes[COCOA_KEYCODE_SIZE];
Papaya::MouseCode CocoaMouseCodes[COCOA_MOUSECODE_SIZE];

void InitCocoaInputCodes()
{
  for (int i = 0; i < COCOA_KEYCODE_SIZE; i++)
    CocoaKeyCodes[i] = Papaya::KeyNone;

  CocoaKeyCodes[0]    = Papaya::KeyA;
  CocoaKeyCodes[11]   = Papaya::KeyB;
  CocoaKeyCodes[8]    = Papaya::KeyC;
  CocoaKeyCodes[2]    = Papaya::KeyD;
  CocoaKeyCodes[14]   = Papaya::KeyE;
  CocoaKeyCodes[3]    = Papaya::KeyF;
  CocoaKeyCodes[5]    = Papaya::KeyG;
  CocoaKeyCodes[4]    = Papaya::KeyH;
  CocoaKeyCodes[34]   = Papaya::KeyI;
  CocoaKeyCodes[38]   = Papaya::KeyJ;
  CocoaKeyCodes[40]   = Papaya::KeyK;
  CocoaKeyCodes[37]   = Papaya::KeyL;
  CocoaKeyCodes[46]   = Papaya::KeyM;
  CocoaKeyCodes[45]   = Papaya::KeyN;
  CocoaKeyCodes[31]   = Papaya::KeyO;
  CocoaKeyCodes[35]   = Papaya::KeyP;
  CocoaKeyCodes[12]   = Papaya::KeyQ;
  CocoaKeyCodes[15]   = Papaya::KeyR;
  CocoaKeyCodes[1]    = Papaya::KeyS;
  CocoaKeyCodes[17]   = Papaya::KeyT;
  CocoaKeyCodes[32]   = Papaya::KeyU;
  CocoaKeyCodes[9]    = Papaya::KeyV;
  CocoaKeyCodes[13]   = Papaya::KeyW;
  CocoaKeyCodes[7]    = Papaya::KeyX;
  CocoaKeyCodes[16]   = Papaya::KeyY;
  CocoaKeyCodes[6]    = Papaya::KeyZ;

  CocoaKeyCodes[29]   = Papaya::Key0;
  CocoaKeyCodes[18]   = Papaya::Key1;
  CocoaKeyCodes[19]   = Papaya::Key2;
  CocoaKeyCodes[20]   = Papaya::Key3;
  CocoaKeyCodes[21]   = Papaya::Key4;
  CocoaKeyCodes[23]   = Papaya::Key5;
  CocoaKeyCodes[22]   = Papaya::Key6;
  CocoaKeyCodes[26]   = Papaya::Key7;
  CocoaKeyCodes[28]   = Papaya::Key8;
  CocoaKeyCodes[25]   = Papaya::Key9; // 10 Numbers

  CocoaKeyCodes[122]  = Papaya::KeyF1;
  CocoaKeyCodes[120]  = Papaya::KeyF2;
  CocoaKeyCodes[99]   = Papaya::KeyF3;
  CocoaKeyCodes[118]  = Papaya::KeyF4;
  CocoaKeyCodes[96]   = Papaya::KeyF5;
  CocoaKeyCodes[97]   = Papaya::KeyF6;
  CocoaKeyCodes[98]   = Papaya::KeyF7;
  CocoaKeyCodes[100]  = Papaya::KeyF8;
  CocoaKeyCodes[101]  = Papaya::KeyF9;
  CocoaKeyCodes[109]  = Papaya::KeyF10;
  CocoaKeyCodes[103]  = Papaya::KeyF11;
  CocoaKeyCodes[111]  = Papaya::KeyF12;
  // CocoaKeyCodes[0] = Papaya::KeyFn; // 13 Fn Keys

  CocoaKeyCodes[27]   = Papaya::KeyDash;
  CocoaKeyCodes[50]   = Papaya::KeyGrave;
  CocoaKeyCodes[24]   = Papaya::KeyEquals;
  CocoaKeyCodes[33]   = Papaya::KeyLeftBracket;
  CocoaKeyCodes[30]   = Papaya::KeyRightBracket;
  CocoaKeyCodes[42]   = Papaya::KeyBackslash;
  CocoaKeyCodes[44]   = Papaya::KeySlash;
  CocoaKeyCodes[47]   = Papaya::KeyPeriod;
  CocoaKeyCodes[43]   = Papaya::KeyComma; // 9 Misc Keys

  // CocoaKeyCodes[0] = Papaya::KeyControl;
  // CocoaKeyCodes[0] = Papaya::KeyAlt;
  CocoaKeyCodes[48]   = Papaya::KeyTab;
  CocoaKeyCodes[53]   = Papaya::KeyEscape;
  CocoaKeyCodes[51]   = Papaya::KeyBackspace;
  // CocoaKeyCodes[0] = Papaya::KeyLeftShift;
  // CocoaKeyCodes[0] = Papaya::KeyRightShift;
  CocoaKeyCodes[36]   = Papaya::KeyEnter; // 8 Modifier Keys

  CocoaKeyCodes[126]  = Papaya::KeyUp;
  CocoaKeyCodes[125]  = Papaya::KeyDown;
  CocoaKeyCodes[123]  = Papaya::KeyLeft;
  CocoaKeyCodes[124]  = Papaya::KeyRight; // 4 Arrow Keys

  for (int i = 0; i < COCOA_MOUSECODE_SIZE; i++)
    CocoaMouseCodes[i] = Papaya::MouseNone;

  CocoaMouseCodes[2] = Papaya::MouseMiddle;
  CocoaMouseCodes[3] = Papaya::Mouse4;
  CocoaMouseCodes[5] = Papaya::Mouse4;
}

Papaya::KeyCode CocoaKeyCodeToPapayaKeyCode(unsigned int keyCode)
{
  if (keyCode < COCOA_KEYCODE_SIZE)
    return CocoaKeyCodes[keyCode];
  else
    PAPAYA_ASSERT(false, "Unknown KeyCode!");
    return Papaya::KeyNone;
}

Papaya::MouseCode CocoaMouseCodeToPapayaMouseCode(unsigned int mouseCode)
{
   if (mouseCode < COCOA_KEYCODE_SIZE)
    return CocoaMouseCodes[mouseCode];
  else
    PAPAYA_ASSERT(false, "Unknown MouseCode!");
    return Papaya::MouseNone;
}

} // namespace Papaya