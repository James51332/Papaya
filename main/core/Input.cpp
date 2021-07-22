#include "papayapch.h"
#include "Input.h"



namespace Papaya
{
  int Input::m_MouseX;
  int Input::m_MouseY;

  bool Input::s_KeyState[PAPAYA_TOTAL_KEYCODES];
  bool Input::s_LastKeyState[PAPAYA_TOTAL_KEYCODES];

  bool Input::s_MouseState[PAPAYA_TOTAL_MOUSECODES];
  bool Input::s_LastMouseState[PAPAYA_TOTAL_MOUSECODES];
    
  int Input::s_AsciiCapital[PAPAYA_TOTAL_KEYCODES];
  int Input::s_AsciiLowercase[PAPAYA_TOTAL_KEYCODES];

  bool Input::KeyPressed(KeyCode key)
  {
    return s_KeyState[key] && !s_LastKeyState[key];
  }

  bool Input::KeyReleased(KeyCode key)
  {
    return !s_KeyState[key] && s_LastKeyState[key];
  }

  bool Input::KeyDown(KeyCode key)
  {
    return s_KeyState[key];
  }

  bool Input::MousePressed(MouseCode btn)
  {
    return s_MouseState[btn] && !s_LastMouseState[btn];
  }

  bool Input::MouseReleased(MouseCode btn)
  {
    return !s_MouseState[btn] && s_LastMouseState[btn];
  }

  bool Input::MouseDown(MouseCode btn)
  {
    return s_MouseState[btn];
  }

  int Input::GetMouseX()
  {
    return m_MouseX;
  }

  int Input::GetMouseY()
  {
    return m_MouseY;
  }

  int Input::ToASCII(KeyCode key, bool capitalized)
  {
    return capitalized ? s_AsciiCapital[key] : s_AsciiLowercase[key];
  }

  void Input::OnInit()
  {
    for (int i = 0; i < PAPAYA_TOTAL_KEYCODES; ++i)
    {
      s_KeyState[i] = false;
      s_LastKeyState[i] = false;
    }

    for (int i = 0; i < PAPAYA_TOTAL_MOUSECODES; ++i)
    {
      s_MouseState[i] = false;
      s_LastMouseState[i] = false;
    }

    memset(&s_AsciiCapital[0], 0, sizeof(s_AsciiCapital));
    memset(&s_AsciiLowercase[0], 0, sizeof(s_AsciiLowercase));

    s_AsciiCapital[KeyA] = 65;
    s_AsciiCapital[KeyB] = 66;
    s_AsciiCapital[KeyC] = 67;
    s_AsciiCapital[KeyD] = 68;
    s_AsciiCapital[KeyE] = 69;
    s_AsciiCapital[KeyF] = 70;
    s_AsciiCapital[KeyG] = 71;
    s_AsciiCapital[KeyH] = 72;
    s_AsciiCapital[KeyI] = 73;
    s_AsciiCapital[KeyJ] = 74;
    s_AsciiCapital[KeyK] = 75;
    s_AsciiCapital[KeyL] = 76;
    s_AsciiCapital[KeyM] = 77;
    s_AsciiCapital[KeyN] = 78;
    s_AsciiCapital[KeyO] = 79;
    s_AsciiCapital[KeyP] = 80;
    s_AsciiCapital[KeyQ] = 81;
    s_AsciiCapital[KeyR] = 82;
    s_AsciiCapital[KeyS] = 83;
    s_AsciiCapital[KeyT] = 84;
    s_AsciiCapital[KeyU] = 85;
    s_AsciiCapital[KeyV] = 86;
    s_AsciiCapital[KeyW] = 87;
    s_AsciiCapital[KeyX] = 88;
    s_AsciiCapital[KeyY] = 89;
    s_AsciiCapital[KeyZ] = 90;
    s_AsciiCapital[Key0] = 41;
    s_AsciiCapital[Key1] = 33;
    s_AsciiCapital[Key2] = 64;
    s_AsciiCapital[Key3] = 35;
    s_AsciiCapital[Key4] = 36;
    s_AsciiCapital[Key5] = 37;
    s_AsciiCapital[Key6] = 94;
    s_AsciiCapital[Key7] = 38;
    s_AsciiCapital[Key8] = 42;
    s_AsciiCapital[Key9] = 41;
    s_AsciiCapital[KeyGrave] = 126;
    s_AsciiCapital[KeyDash] = 95;
    s_AsciiCapital[KeyEquals] = 43;
    s_AsciiCapital[KeyLeftBracket] = 123;
    s_AsciiCapital[KeyRightBracket] = 125;
    s_AsciiCapital[KeyBackslash] = 124;
    s_AsciiCapital[KeySlash] = 63;
    s_AsciiCapital[KeyPeriod] = 62;
    s_AsciiCapital[KeyComma] = 60; 
    s_AsciiCapital[KeyTab] = 9;
    s_AsciiCapital[KeyEscape] = 27;
    s_AsciiCapital[KeyBackspace] = 8;
    s_AsciiLowercase[KeySpace] = 32;

    s_AsciiLowercase[KeyA] = 97;
    s_AsciiLowercase[KeyB] = 98;
    s_AsciiLowercase[KeyC] = 99;
    s_AsciiLowercase[KeyD] = 100;
    s_AsciiLowercase[KeyE] = 101;
    s_AsciiLowercase[KeyF] = 102;
    s_AsciiLowercase[KeyG] = 103;
    s_AsciiLowercase[KeyH] = 104;
    s_AsciiLowercase[KeyI] = 105;
    s_AsciiLowercase[KeyJ] = 106;
    s_AsciiLowercase[KeyK] = 107;
    s_AsciiLowercase[KeyL] = 108;
    s_AsciiLowercase[KeyM] = 109;
    s_AsciiLowercase[KeyN] = 110;
    s_AsciiLowercase[KeyO] = 111;
    s_AsciiLowercase[KeyP] = 112;
    s_AsciiLowercase[KeyQ] = 113;
    s_AsciiLowercase[KeyR] = 114;
    s_AsciiLowercase[KeyS] = 115;
    s_AsciiLowercase[KeyT] = 116;
    s_AsciiLowercase[KeyU] = 117;
    s_AsciiLowercase[KeyV] = 118;
    s_AsciiLowercase[KeyW] = 119;
    s_AsciiLowercase[KeyX] = 120;
    s_AsciiLowercase[KeyY] = 121;
    s_AsciiLowercase[KeyZ] = 122;
    s_AsciiLowercase[Key0] = 48;
    s_AsciiLowercase[Key1] = 49;
    s_AsciiLowercase[Key2] = 50;
    s_AsciiLowercase[Key3] = 51;
    s_AsciiLowercase[Key4] = 52;
    s_AsciiLowercase[Key5] = 53;
    s_AsciiLowercase[Key6] = 54;
    s_AsciiLowercase[Key7] = 55;
    s_AsciiLowercase[Key8] = 56;
    s_AsciiLowercase[Key9] = 57;
    s_AsciiLowercase[KeyGrave] = 96;
    s_AsciiLowercase[KeyDash] = 45;
    s_AsciiLowercase[KeyEquals] = 61;
    s_AsciiLowercase[KeyLeftBracket] = 91;
    s_AsciiLowercase[KeyRightBracket] = 93;
    s_AsciiLowercase[KeyBackslash] = 92;
    s_AsciiLowercase[KeySlash] = 47;
    s_AsciiLowercase[KeyPeriod] = 46;
    s_AsciiLowercase[KeyComma] = 44;
    s_AsciiLowercase[KeyTab] = 9;
    s_AsciiLowercase[KeyEscape] = 27;
    s_AsciiLowercase[KeyBackspace] = 8;
    s_AsciiLowercase[KeySpace] = 32;
  }

  void Input::OnUpdate()
  {
    memcpy(s_LastKeyState, s_KeyState, sizeof(s_KeyState));
    memcpy(s_LastMouseState, s_MouseState, sizeof(s_MouseState));
  }

  void Input::OnEvent(const Scope<Event>& event)
  {
    if (!(event->GetCategoryFlags() & EventCategoryInput))
      return;

    EventDispatcher::Dispatch<KeyPressEvent>(event, [](KeyPressEvent* e) {
      Input::s_KeyState[e->GetKeyCode()] = true;
      });

    EventDispatcher::Dispatch<KeyReleaseEvent>(event, [](KeyReleaseEvent* e) {
      Input::s_KeyState[e->GetKeyCode()] = false;
      });

    EventDispatcher::Dispatch<MousePressEvent>(event, [](MousePressEvent* e) {
      Input::s_MouseState[e->GetMouseCode()] = true;
      });

    EventDispatcher::Dispatch<MouseReleaseEvent>(event, [](MouseReleaseEvent* e) {
      Input::s_MouseState[e->GetMouseCode()] = false;
      });

    EventDispatcher::Dispatch<MouseMoveEvent>(event, [](MouseMoveEvent* event)
      {
        m_MouseX = static_cast<int>(event->GetXPosition());
        m_MouseY = static_cast<int>(event->GetYPosition());
      });
  }

} // namespace Papaya
