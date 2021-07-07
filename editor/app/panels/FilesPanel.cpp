#include "FilesPanel.h"

#include <imgui/imgui.h>
#include <filesystem>

namespace Papaya
{
  FilesPanel::FilesPanel()
  {
    m_CurrentDirectory = ".";
  }

  FilesPanel::FilesPanel(Ref<Scene>& scene)
  {
    m_Scene = scene;
    m_CurrentDirectory = ".";
  }

  FilesPanel::~FilesPanel()
  {
  }

  void FilesPanel::OnImGuiRender()
  {
    if (m_Open)
    {
      ImGui::Begin("File Explorer");

      if (m_CurrentDirectory != ".")
      {
        if (ImGui::Button("Back"))
        {
          // It's midnight so I decided to manually find the parent
          // directory but in retrospect there is probably a better way...
          for (int i = static_cast<int>(m_CurrentDirectory.Length()) - 1; i >= 0; --i)
            if (m_CurrentDirectory[i] == '/')
            {
              m_CurrentDirectory.MakeSubstring(0, i - 1);
              break;
            }
        }

        if (m_CurrentDirectory.Length() > 2)
        {
          ImGui::SameLine();
          ImGui::Text(m_CurrentDirectory.Substring(2, static_cast<int>(m_CurrentDirectory.Length()) - 1).Raw());
        }
        ImGui::Separator();
      }

      ImGui::BeginChild("Files");
      for (const auto& entry : std::filesystem::directory_iterator(m_CurrentDirectory.Raw()))
      {
        if (entry.is_directory())
        {
          if (ImGui::Button(entry.path().filename().string().c_str()))
            m_CurrentDirectory = m_CurrentDirectory + "/" + entry.path().filename().string().c_str();
        }
        else
        {
          ImGui::Text(entry.path().filename().string().c_str());
        }
      }
      ImGui::EndChild();
      ImGui::End();
    }
  }
} // namespace Papaya