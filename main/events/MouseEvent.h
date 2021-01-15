#ifndef MouseEvent_h
#define MouseEvent_h

#include "Event.h"

namespace Papaya
{

class MouseButtonEvent : public Event {
public:
  int GetMouseCode() const { return m_MouseCode; }

  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

protected:
  MouseButtonEvent(int mouseCode)
    : m_MouseCode(mouseCode) {}

  int m_MouseCode;
};

class MousePressEvent : public MouseButtonEvent {
public:
  MousePressEvent(int mouseCode)
    : MouseButtonEvent(mouseCode) {}

  EVENT_CLASS_TYPE(EventType::MousePress);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "MousePressEvent: " << m_MouseCode;
    return ss.str();
  }
};

class MouseReleaseEvent : public MouseButtonEvent {
public:
  MouseReleaseEvent(int mouseCode)
    : MouseButtonEvent(mouseCode) {}

  EVENT_CLASS_TYPE(EventType::MouseRelease);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseReleaseEvent: " << m_MouseCode;
    return ss.str();
  }
};

class MouseScrollEvent : public Event {
public:
  MouseScrollEvent(int xScroll, int yScroll)
    : m_XScroll(xScroll), m_YScroll(yScroll) {}

  inline int GetXScroll() const { return m_XScroll; }
  inline int GetYScroll() const { return m_YScroll; }

  EVENT_CLASS_TYPE(EventType::MouseScroll);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrollEvent: " << m_YScroll << "vertical (" << m_XScroll << "horizantal)";
    return ss.str();
  }
private:
  int m_XScroll, m_YScroll;
};

class MouseMoveEvent : public Event {
public:
  MouseMoveEvent(float mouseX, float mouseY)
    : m_MouseX(mouseX), m_MouseY(mouseY) {}

  inline float GetXPosition() const { return m_MouseX; }
  inline float GetYPosition() const { return m_MouseY; }

  EVENT_CLASS_TYPE(EventType::MouseMove);

  virtual std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMoveEvent: (x: " << m_MouseX << ", y: " << m_MouseY << ")";
    return ss.str();
  }
private:
  float m_MouseX, m_MouseY;
};

} // namespace Papaya


#endif /* end of include guard: MouseEvent_h */