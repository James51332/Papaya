#pragma once

namespace Papaya {

class Panel
{
public:
  virtual ~Panel() {}

  void Show() { m_Open = true; }
  void Hide() { m_Open = false; }
  void ToggleVisibility() { m_Open = !m_Open; }

  virtual void OnImGuiRender() = 0;

protected:
  bool m_Open = true;
};

} // namespace Papaya
