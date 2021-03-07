#pragma once

#include "Event.h"
#include "main/core/KeyCode.h"

namespace Papaya
{

  class KeyEvent : public Event
  {
  public:
    inline KeyCode GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

  protected:
    KeyEvent(KeyCode keyCode)
        : m_KeyCode(keyCode) {}

    KeyCode m_KeyCode;
  };

  class KeyPressEvent : public KeyEvent
  {
  public:
    KeyPressEvent(KeyCode keyCode)
        : KeyEvent(keyCode) {}

    EVENT_CLASS_TYPE(KeyPress);

    virtual String ToString() const override
    {
      std::stringstream ss;
      ss << "KeyPressEvent: " << m_KeyCode;
      return ss.str().c_str();
    }
  };

  class KeyReleaseEvent : public KeyEvent
  {
  public:
    KeyReleaseEvent(KeyCode keyCode)
        : KeyEvent(keyCode) {}

    EVENT_CLASS_TYPE(KeyRelease);

    virtual String ToString() const override
    {
      std::stringstream ss;
      ss << "KeyReleaseEvent: " << m_KeyCode;
      return ss.str().c_str();
    }
  };

  class KeyRepeatEvent : public KeyEvent
  {
  public:
    KeyRepeatEvent(KeyCode keyCode, int repeatCount)
        : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

    EVENT_CLASS_TYPE(KeyRepeat);

    virtual String ToString() const override
    {
      std::stringstream ss;
      ss << "KeyRepeatEvent:" << m_KeyCode << "(" << m_KeyCode << " repeats)";
      return ss.str().c_str();
    }

  private:
    int m_RepeatCount;
  };

} // namespace Papaya
