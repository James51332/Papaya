#pragma once

#include "Event.h"

namespace Papaya
{

class WindowCloseEvent : public Event {
public:
  WindowCloseEvent() {}

  EVENT_CLASS_CATEGORY(EventCategoryWindow);
  EVENT_CLASS_TYPE(WindowClose);

  virtual String ToString() const override {
    std::stringstream ss;
    ss << "WindowCloseEvent:";
    return ss.str().c_str();
  }
};

class WindowFocusEvent : public Event {
public:
  WindowFocusEvent() {}

  EVENT_CLASS_CATEGORY(EventCategoryWindow);
  EVENT_CLASS_TYPE(WindowFocus);

  virtual String ToString() const override {
    std::stringstream ss;
    ss << "WindowFocusEvent:";
    return ss.str().c_str();
  }
};

class WindowLoseFocusEvent : public Event {
public:
  WindowLoseFocusEvent() {}

  EVENT_CLASS_CATEGORY(EventCategoryWindow);
  EVENT_CLASS_TYPE(WindowLoseFocus);

  virtual String ToString() const override {
    std::stringstream ss;
    ss << "WindowLoseFocusEvent:";
    return ss.str().c_str();
  }
};

class WindowResizeEvent : public Event {
public:
  WindowResizeEvent(float width, float height)
    : m_Width(width), m_Height(height) {}

  inline float GetWidth() const { return m_Width; }
  inline float GetHeight() const { return m_Height; }

  EVENT_CLASS_CATEGORY(EventCategoryWindow);
  EVENT_CLASS_TYPE(WindowResize);

  virtual String ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: (width: " << m_Width << ", height: " << m_Height << ")";
    return ss.str().c_str();
  }

private:
  float m_Width, m_Height;
};

} // namespace Papaya