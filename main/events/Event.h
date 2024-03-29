#pragma once

// Based off of TheCherno/Hazel Event System
// https://github.com/TheCherno/Hazel

namespace Papaya
{

  enum class EventType
  {
    None,
    MousePress,
    MouseRelease,
    MouseScroll,
    MouseMove,
    KeyPress,
    KeyRelease,
    KeyRepeat,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLoseFocus,
  };

#define BIT(x) (1 << x)
  enum EventCategory
  {
    None = 0,
    EventCategoryKeyboard = BIT(0),
    EventCategoryMouse = BIT(1),
    EventCategoryWindow = BIT(2),
    EventCategoryInput = BIT(3),
  };

#define EVENT_CLASS_TYPE(TYPE)                                                \
  static EventType GetStaticType() { return EventType::TYPE; }                \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const char *GetName() const override { return #TYPE; }

#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

  class Event
  {
  public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char *GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual String ToString() const { return GetName(); }

    bool IsInCategory(EventCategory category) { return category & GetCategoryFlags(); }

  protected:
    EventType m_Type = EventType::None;
    EventCategory m_Category = EventCategory::None;
  };

  class EventDispatcher
  {
  public:
    template <typename T, typename F>
    static bool Dispatch(const Scope<Event> &event, const F &func)
    {
      if (event->GetEventType() == T::GetStaticType())
      {
        if (!event->Handled)
          func(static_cast<T *>(event.get()));
        return true;
      }
      return false;
    }
  };

  inline std::ostream &operator<<(std::ostream &os, const Event &e)
  {
    return os << e.ToString();
  }

  inline std::ostream &operator<<(std::ostream &os, const Scope<Event> &e)
  {
    return os << e->ToString();
  }

} // namespace Papaya