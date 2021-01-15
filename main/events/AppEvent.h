#ifndef AppEvent_h
#define AppEvent_h

#include "Event.h"

namespace Papaya
{

class WindowCloseEvent : public Event {
public:
  WindowCloseEvent() {}

  EVENT_CLASS_CATEGORY(EventCategoryWindow);
  EVENT_CLASS_TYPE(EventType::WindowClose);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowCloseEvent:";
    return ss.str();
  }
};

class WindowFocusEvent : public Event {
public:
  WindowFocusEvent() {}

  EVENT_CLASS_CATEGORY(EventCategoryWindow);
  EVENT_CLASS_TYPE(EventType::WindowFocus);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowFocusEvent:";
    return ss.str();
  }
};

class WindowLoseFocusEvent : public Event {
public:
  WindowLoseFocusEvent() {}

  EVENT_CLASS_CATEGORY(EventCategoryWindow);
  EVENT_CLASS_TYPE(EventType::WindowLoseFocus);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowLoseFocusEvent:";
    return ss.str();
  }
};

class WindowResizeEvent : public Event {
public:
  WindowResizeEvent(float width, float height)
    : m_Width(width), m_Height(height) {}

  inline float GetWidth() const { return m_Width; }
  inline float GetHeight() const { return m_Height; }

  EVENT_CLASS_CATEGORY(EventCategoryWindow);
  EVENT_CLASS_TYPE(EventType::WindowResize);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: (width: " << m_Width << ", height: " << m_Height << ")";
    return ss.str();
  }

private:
  float m_Width, m_Height;
};

} // namespace Papaya

#endif /* end of include guard: AppEvent_h */