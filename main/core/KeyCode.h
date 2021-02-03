#ifndef KeyCode_h
#define KeyCode_h

namespace Papaya
{

enum KeyCode
{
  KeyNone = 0,
  KeyA,
  KeyB,
  KeyC,
  KeyD,
  KeyE,
  KeyF,
  KeyG,
  KeyH,
  KeyI,
  KeyJ,
  KeyK,
  KeyL,
  KeyM,
  KeyN,
  KeyO,
  KeyP,
  KeyQ,
  KeyR,
  KeyS,
  KeyT,
  KeyU,
  KeyV,
  KeyW,
  KeyX,
  KeyY,
  KeyZ, // 26 Letters

  Key0,
  Key1,
  Key2,
  Key3,
  Key4,
  Key5,
  Key6,
  Key7,
  Key8,
  Key9, // 10 Numbers

  KeyF1,
  KeyF2,
  KeyF3,
  KeyF4,
  KeyF5,
  KeyF6,
  KeyF7,
  KeyF8,
  KeyF9,
  KeyF10,
  KeyF11,
  KeyF12,
  KeyFn, // 13 Function Keys

  KeyGrave,
  KeyDash,
  KeyEquals,
  KeyLeftBracket,
  KeyRightBracket,
  KeyBackslash,
  KeySlash,
  KeyPeriod,
  KeyComma, // 9 Misc Keys

  KeyControl,
  KeyAlt,
  KeyCaps,
  KeyTab,
  KeyEscape,
  KeyBackspace,
  KeyShift,
  KeyEnter, // 8 Modifier Keys

  KeyUp,
  KeyDown,
  KeyLeft,
  KeyRight // 4 Arrow Keys

}; // 72 Total Keys

#define PAPAYA_TOTAL_KEYCODES 73

} // namespace Papaya


#endif /* end of include guard: KeyCode_h */