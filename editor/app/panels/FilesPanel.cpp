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

  static void DisplayPath(String& path)
  {
    if (path != ".")
    {
      if (ImGui::Button("Back"))
      {
        // TODO: Look into std::relative()
        // It's midnight so I decided to manually find the parent
        // directory but in retrospect there is probably a better way...
        for (int i = static_cast<int>(path.Length()) - 1; i >= 0; --i)
          if (path[i] == '/')
          {
            path.MakeSubstring(0, i - 1);
            break;
          }
      }

      if (path.Length() > 2)
      {
        ImGui::SameLine();
        ImGui::Text(path.Substring(2, static_cast<int>(path.Length()) - 1).Raw());
      }
      ImGui::Separator();
    }

  }

  void FilesPanel::OnImGuiRender()
  {
    if (m_Open)
    {
      ImGui::Begin("File Explorer");

      DisplayPath(m_CurrentDirectory);
      ImGui::BeginChild("Files");

      static float size = 100.0f;
      static float padding = 16.0f;
      float width = ImGui::GetContentRegionAvail().x;
      int cols = static_cast<int>(width / (size + padding));

      ImGui::Columns(cols != 0 ? cols : 1, 0, false);
      for (const auto& entry : std::filesystem::directory_iterator(m_CurrentDirectory.Raw()))
      {
        String name = entry.path().filename().string().c_str();

        if (ImGui::Button(name.Raw(), { size, size }))
        {
          if (entry.is_directory())
            m_CurrentDirectory = m_CurrentDirectory + "/" + name;
        }
        ImGui::Text(name.Raw());
        ImGui::NextColumn();
      }
      ImGui::EndChild();
      ImGui::End();
    }
  }
} // namespace Papaya