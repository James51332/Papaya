#include "Input.h"

#include "main/core/Log.h"

namespace Papaya
{
  
bool Input::s_KeyState[PAPAYA_TOTAL_KEYCODES];
bool Input::s_LastKeyState[PAPAYA_TOTAL_KEYCODES];

bool Input::s_MouseState[PAPAYA_TOTAL_MOUSECODES];
bool Input::s_LastMouseState[PAPAYA_TOTAL_MOUSECODES];

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
}

} // namespace Papaya
