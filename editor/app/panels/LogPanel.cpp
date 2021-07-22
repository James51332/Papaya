#include "papayapch.h"
#include "LogPanel.h"



#include <imgui/imgui.h>

namespace Papaya
{
  LogPanel::LogPanel()
  {
  }

  LogPanel::LogPanel(Ref<Scene>& scene)
  {
  }

  LogPanel::~LogPanel()
  {
  }

  void LogPanel::OnImGuiRender()
  {
    if (m_Open)
    {
      ImGui::Begin("Output");
      ImGui::Text(Log::GetClientStream().str().c_str());
      ImGui::End();
    }
  }
} // namespace Papaya