#pragma once

#include <imgui/imgui.h>      // IMGUI_IMPL_API


namespace Papaya {

// Backend API
IMGUI_IMPL_API bool     ImGui_Init();
IMGUI_IMPL_API void     ImGui_Render();

// (Optional) Called by Init/NewFrame/Shutdown
IMGUI_IMPL_API bool     ImGui_CreateFontsTexture();
IMGUI_IMPL_API bool     ImGui_CreateDeviceObjects();
IMGUI_IMPL_API void     ImGui_DestroyDeviceObjects();

}
