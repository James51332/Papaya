#include "WindowsInputCode.h"

#include "main/core/Log.h"

namespace Papaya
{

#define Win32_KEYCODE_SIZE 256
#define Win32_MOUSECODE_SIZE 10

  Papaya::KeyCode Win32KeyCodes[Win32_KEYCODE_SIZE];
  Papaya::MouseCode Win32MouseCodes[Win32_MOUSECODE_SIZE];

  void InitWin32InputCodes()
  {
    for (int i = 0; i < Win32_KEYCODE_SIZE; i++)
      Win32KeyCodes[i] = Papaya::KeyNone;

    Win32KeyCodes[0x41] = Papaya::KeyA;
    Win32KeyCodes[0x42] = Papaya::KeyB;
    Win32KeyCodes[0x43] = Papaya::KeyC;
    Win32KeyCodes[0x44] = Papaya::KeyD;
    Win32KeyCodes[0x45] = Papaya::KeyE;
    Win32KeyCodes[0x46] = Papaya::KeyF;
    Win32KeyCodes[0x47] = Papaya::KeyG;
    Win32KeyCodes[0x48] = Papaya::KeyH;
    Win32KeyCodes[0x49] = Papaya::KeyI;
    Win32KeyCodes[0x4a] = Papaya::KeyJ;
    Win32KeyCodes[0x4b] = Papaya::KeyK;
    Win32KeyCodes[0x4c] = Papaya::KeyL;
    Win32KeyCodes[0x4d] = Papaya::KeyM;
    Win32KeyCodes[0x4e] = Papaya::KeyN;
    Win32KeyCodes[0x4f] = Papaya::KeyO;
    Win32KeyCodes[0x50] = Papaya::KeyP;
    Win32KeyCodes[0x51] = Papaya::KeyQ;
    Win32KeyCodes[0x52] = Papaya::KeyR;
    Win32KeyCodes[0x53] = Papaya::KeyS;
    Win32KeyCodes[0x54] = Papaya::KeyT;
    Win32KeyCodes[0x55] = Papaya::KeyU;
    Win32KeyCodes[0x56] = Papaya::KeyV;
    Win32KeyCodes[0x57] = Papaya::KeyW;
    Win32KeyCodes[0x58] = Papaya::KeyX;
    Win32KeyCodes[0x59] = Papaya::KeyY;
    Win32KeyCodes[0x5a] = Papaya::KeyZ;

    Win32KeyCodes[0x30] = Papaya::Key0;
    Win32KeyCodes[0x31] = Papaya::Key1;
    Win32KeyCodes[0x32] = Papaya::Key2;
    Win32KeyCodes[0x33] = Papaya::Key3;
    Win32KeyCodes[0x34] = Papaya::Key4;
    Win32KeyCodes[0x35] = Papaya::Key5;
    Win32KeyCodes[0x36] = Papaya::Key6;
    Win32KeyCodes[0x37] = Papaya::Key7;
    Win32KeyCodes[0x38] = Papaya::Key8;
    Win32KeyCodes[0x39] = Papaya::Key9; // 10 Numbers

    Win32KeyCodes[0x70] = Papaya::KeyF1;
    Win32KeyCodes[0x71] = Papaya::KeyF2;
    Win32KeyCodes[0x72] = Papaya::KeyF3;
    Win32KeyCodes[0x73] = Papaya::KeyF4;
    Win32KeyCodes[0x74] = Papaya::KeyF5;
    Win32KeyCodes[0x75] = Papaya::KeyF6;
    Win32KeyCodes[0x76] = Papaya::KeyF7;
    Win32KeyCodes[0x77] = Papaya::KeyF8;
    Win32KeyCodes[0x78] = Papaya::KeyF9;
    Win32KeyCodes[0x79] = Papaya::KeyF10;
    Win32KeyCodes[0x7a] = Papaya::KeyF11;
    Win32KeyCodes[0x7b] = Papaya::KeyF12;
    Win32KeyCodes[0x7c] = Papaya::KeyFn; // 13 Fn Keys

    Win32KeyCodes[189] = Papaya::KeyDash;
    Win32KeyCodes[192] = Papaya::KeyGrave;
    Win32KeyCodes[187] = Papaya::KeyEquals;
    Win32KeyCodes[219] = Papaya::KeyLeftBracket;
    Win32KeyCodes[221] = Papaya::KeyRightBracket;
    Win32KeyCodes[220] = Papaya::KeyBackslash;
    Win32KeyCodes[191] = Papaya::KeySlash;
    Win32KeyCodes[0xbe] = Papaya::KeyPeriod;
    Win32KeyCodes[0xbc] = Papaya::KeyComma; // 9 Misc Keys

    Win32KeyCodes[0x20] = Papaya::KeySpace;

    Win32KeyCodes[0x11] = Papaya::KeyControl;
    Win32KeyCodes[0xa2] = Papaya::KeyControl;
    Win32KeyCodes[0xa3] = Papaya::KeyControl;
    Win32KeyCodes[0x14] = Papaya::KeyCaps;
    Win32KeyCodes[0x12] = Papaya::KeyAlt;
    Win32KeyCodes[0x09] = Papaya::KeyTab;
    Win32KeyCodes[0x1b] = Papaya::KeyEscape;
    Win32KeyCodes[0x08] = Papaya::KeyBackspace;
    Win32KeyCodes[0x10] = Papaya::KeyShift;
    Win32KeyCodes[0x0D] = Papaya::KeyEnter; // 8 Modifier Keys

    Win32KeyCodes[0x26] = Papaya::KeyUp;
    Win32KeyCodes[0x28] = Papaya::KeyDown;
    Win32KeyCodes[0x25] = Papaya::KeyLeft;
    Win32KeyCodes[0x27] = Papaya::KeyRight; // 4 Arrow Keys

    for (int i = 0; i < Win32_MOUSECODE_SIZE; i++)
      Win32MouseCodes[i] = Papaya::MouseNone;

    Win32MouseCodes[1] = Papaya::Mouse4;
    Win32MouseCodes[2] = Papaya::Mouse4;
  }

  Papaya::KeyCode Win32KeyCodeToPapayaKeyCode(unsigned int keyCode)
  {
    if (keyCode < Win32_KEYCODE_SIZE)
      return Win32KeyCodes[keyCode];
    else
      PAPAYA_ASSERT(false, "Unknown KeyCode!");
    return Papaya::KeyNone;
  }

} // namespace Papaya
