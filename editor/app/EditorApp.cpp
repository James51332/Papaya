#include "papayapch.h"
#include "EditorApp.h"

#include "EditorLayer.h"

namespace Papaya
{

  EditorApp::EditorApp()
  {
    PushLayer(new EditorLayer());
  }

  EditorApp::~EditorApp()
  {

  }

  Game* CreateGame() {
    return new EditorApp();
  }

} // namespace Papaya
