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

  EVENT_CLASS_TYPE(MousePress);

  virtual String ToString() const override {
    std::stringstream ss;
    ss << "MousePressEvent: " << m_MouseCode;
    return ss.str().c_str();
  }
};

class MouseReleaseEvent : public MouseButtonEvent {
public:
  MouseReleaseEvent(int mouseCode)
    : MouseButtonEvent(mouseCode) {}

  EVENT_CLASS_TYPE(MouseRelease);

  virtual String ToString() const override {
    std::stringstream ss;
    ss << "MouseReleaseEvent: " << m_MouseCode;
    return ss.str().c_str();
  }
};

class MouseScrollEvent : public Event {
public:
  MouseScrollEvent(int xScroll, int yScroll)
    : m_XScroll(xScroll), m_YScroll(yScroll) {}

  inline int GetXScroll() const { return m_XScroll; }
  inline int GetYScroll() const { return m_YScroll; }

  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
  EVENT_CLASS_TYPE(MouseScroll);

  virtual String ToString() const override {
    std::stringstream ss;
    ss << "MouseScrollEvent: " << m_YScroll << "vertical (" << m_XScroll << "horizantal)";
    return ss.str().c_str();
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

  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
  EVENT_CLASS_TYPE(MouseMove);

  virtual String ToString() const override {
    std::stringstream ss;
    ss << "MouseMoveEvent: (x: " << m_MouseX << ", y: " << m_MouseY << ")";
    return ss.str().c_str();
  }
private:
  float m_MouseX, m_MouseY;
};

} // namespace Papaya


#endif /* end of include guard: MouseEvent_h */