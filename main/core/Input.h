#pragma once

#include "MouseCode.h"
#include "KeyCode.h"

#include "main/events/Event.h"
#include "main/events/KeyEvent.h"
#include "main/events/MouseEvent.h"

namespace Papaya
{

  class Game;

  class Input
  {
    friend class Game;

  public:
    static bool KeyPressed(KeyCode key);  // only true for one frame
    static bool KeyReleased(KeyCode key); // true as long as key is down
    static bool KeyDown(KeyCode key);     // only true for one frame on release

    static bool MousePressed(MouseCode btn);  // only true for one frame
    static bool MouseReleased(MouseCode btn); // true as long as key is down
    static bool MouseDown(MouseCode btn);     // only true for one frame on release

  private:
    static void OnInit();
    static void OnUpdate(); // called once per frame and sets the current state to the previous state
    static void OnEvent(const Scope<Event> &event);

  private:
    static bool s_KeyState[PAPAYA_TOTAL_KEYCODES];
    static bool s_LastKeyState[PAPAYA_TOTAL_KEYCODES];

    static bool s_MouseState[PAPAYA_TOTAL_MOUSECODES];
    static bool s_LastMouseState[PAPAYA_TOTAL_MOUSECODES];
  };

} // namespace Papaya
