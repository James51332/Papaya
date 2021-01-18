#ifndef KeyEvent_h
#define KeyEvent_h

#include "Event.h"

namespace Papaya
{

class KeyEvent : public Event {
public:
  inline int GetKeyCode() const { return m_KeyCode; }

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

protected:
  KeyEvent(int keyCode)
    : m_KeyCode(keyCode) {}

  int m_KeyCode;
};

class KeyPressEvent : public KeyEvent {
public:
  KeyPressEvent(int keyCode)
    : KeyEvent(keyCode) {}

  EVENT_CLASS_TYPE(KeyPress);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressEvent: " << m_KeyCode;
    return ss.str();
  }
};

class KeyReleaseEvent : public KeyEvent {
public:
  KeyReleaseEvent(int keyCode)
    : KeyEvent(keyCode) {}

  EVENT_CLASS_TYPE(KeyRelease);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleaseEvent: " << m_KeyCode;
    return ss.str();
  }
};

class KeyRepeatEvent : public KeyEvent {
public:
  KeyRepeatEvent(int keyCode, int repeatCount)
    : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

  EVENT_CLASS_TYPE(KeyRepeat);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyRepeatEvent:" << m_KeyCode << "(" << m_KeyCode << " repeats)";
    return ss.str();
  }

private:
  int m_RepeatCount;
};

} // namespace Papaya

#endif /* end of include guard: KeyEvent_h */
