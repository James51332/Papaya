#include "papayapch.h"
#include "ImGuiRenderer.h"

#include "main/core/Game.h"
#include "main/core/KeyCode.h"
#include "main/core/Input.h"

#include "main/renderer/BufferLayout.h"
#include "main/renderer/Buffer.h"
#include "main/renderer/Shader.h"
#include "main/renderer/Texture.h"
#include "main/renderer/PipelineState.h"
#include "main/renderer/RenderCommand.h"

#include "main/events/Event.h"
#include "main/events/KeyEvent.h"
#include "main/events/MouseEvent.h"
#include "main/events/AppEvent.h"




#include <imgui/imgui.h>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Papaya
{

  struct ImGuiRenderData
  {
    Ref<Buffer> ImGuiVertexBuffer;
    Ref<Buffer> ImGuiIndexBuffer;
    Ref<PipelineState> ImGuiPipelineState;

    Ref<Texture2D> ImGuiTexture;

    float Width, Height;

    bool BlockEvents = false;
  };

  static ImGuiRenderData s_Data;

  void ImGuiRenderer::OnInit()
  {
    ImGui::CreateContext();

    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
    colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
    colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_DockingPreview] = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

    style->ChildRounding = 4.0f;
    style->FrameBorderSize = 1.0f;
    style->FrameRounding = 2.0f;
    style->GrabMinSize = 7.0f;
    style->PopupRounding = 2.0f;
    style->ScrollbarRounding = 12.0f;
    style->ScrollbarSize = 13.0f;
    style->TabBorderSize = 1.0f;
    style->TabRounding = 0.0f;
    style->WindowRounding = 4.0f;

    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "Papaya Renderer";
    io.BackendPlatformName = "Papaya Engine";

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    io.ConfigDockingWithShift = false;

    io.Fonts->AddFontFromFileTTF("resources/fonts/Roboto-Medium.ttf", 14);

    s_Data.Width = static_cast<float>(Game::Get()->GetWindow()->GetAttribs().Width);
    s_Data.Height = static_cast<float>(Game::Get()->GetWindow()->GetAttribs().Height);
    io.DisplaySize.x = s_Data.Width;
    io.DisplaySize.y = s_Data.Height;

    io.KeyMap[ImGuiKey_Tab] = KeyTab;
    io.KeyMap[ImGuiKey_LeftArrow] = KeyLeft;
    io.KeyMap[ImGuiKey_RightArrow] = KeyRight;
    io.KeyMap[ImGuiKey_UpArrow] = KeyUp;
    io.KeyMap[ImGuiKey_DownArrow] = KeyDown;
    // io.KeyMap[ImGuiKey_PageUp]      = KeyPageUp;
    // io.KeyMap[ImGuiKey_PageDown]    = KeyPageDown;
    // io.KeyMap[ImGuiKey_Home]        = KeyHome;
    // io.KeyMap[ImGuiKey_End]         = KeyEnd;
    // io.KeyMap[ImGuiKey_Insert]      = KeyInsert;
    // io.KeyMap[ImGuiKey_Delete]      = KeyDelete;
    io.KeyMap[ImGuiKey_Backspace] = KeyBackspace;
    io.KeyMap[ImGuiKey_Space] = KeySpace;
    io.KeyMap[ImGuiKey_Enter] = KeyEnter;
    io.KeyMap[ImGuiKey_Escape] = KeyEscape;
    //io.KeyMap[ImGuiKey_KeyPadEnter] = KeyKeyPadEnter;
    io.KeyMap[ImGuiKey_A] = KeyA;
    io.KeyMap[ImGuiKey_C] = KeyC;
    io.KeyMap[ImGuiKey_V] = KeyV;
    io.KeyMap[ImGuiKey_X] = KeyX;
    io.KeyMap[ImGuiKey_Y] = KeyY;
    io.KeyMap[ImGuiKey_Z] = KeyZ;

    String vertexSrc = R"(
    #version 410 core
    
    layout (location = 0) in vec2 a_Pos;
    layout (location = 1) in vec2 a_UV;
    layout (location = 2) in vec4 a_Color;
    
    out vec2 v_UV;
    out vec4 v_Color;
    
    uniform mat4 u_Projection;
    
    void main()
    {
      v_UV = a_UV;
      v_Color = a_Color;
      gl_Position = u_Projection * vec4(a_Pos.xy, 0, 1);
    })";

    String fragmentSrc = R"(
    #version 410 core
    
    layout (location = 0) out vec4 FragColor;
    
    in vec2 v_UV;
    in vec4 v_Color;
    
    uniform sampler2D u_Texture;
    
    void main()
    {
        FragColor = v_Color * texture(u_Texture, v_UV.st);
    })";

    Ref<Shader> shader = Shader::Create(vertexSrc, fragmentSrc);

    VertexDescriptor layout = { {{ShaderDataType::Float2, "a_Pos"},
                                {ShaderDataType::Float2, "a_UV"},
                                {ShaderDataType::Byte, "a_Color", true}} };

    s_Data.ImGuiPipelineState = PipelineState::Create({ shader, layout });

    s_Data.ImGuiVertexBuffer = Buffer::Create();
    s_Data.ImGuiIndexBuffer = Buffer::Create();

    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    s_Data.ImGuiTexture = Texture2D::Create(pixels, width, height, ChannelType::RGBA);
    // TODO: Load as RGBA 32-bit (75% of the memory is wasted, but default font
    // is so small). Consider moving to Alpha8() for the texture;
  }

  void ImGuiRenderer::OnTerminate()
  {
  }

  void ImGuiRenderer::Begin(Timestep ts) 
  {
    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = static_cast<float>(ts);

    ImGui::NewFrame();
  }

  void ImGuiRenderer::End()
  {
    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();

    ImGuiIO &io = ImGui::GetIO();

    int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
    int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
    if (fb_width <= 0 || fb_height <= 0)
      return;

    ImVec2 clip_off = draw_data->DisplayPos;         // (0,0) unless using multi-viewports
    ImVec2 clip_scale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;

    glm::mat4 ortho = glm::ortho(L, R, B, T);

    s_Data.ImGuiPipelineState->GetShader()->Bind();
    s_Data.ImGuiPipelineState->GetShader()->SetInt("u_Texture", 0);
    s_Data.ImGuiPipelineState->GetShader()->SetMat4("u_Projection", ortho);

    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
      const ImDrawList* cmd_list = draw_data->CmdLists[n];

      s_Data.ImGuiVertexBuffer->Reset(cmd_list->VtxBuffer.Data,
        cmd_list->VtxBuffer.Size * sizeof(ImDrawVert),
        BufferType::Vertex,
        BufferUsage::Stream);

      s_Data.ImGuiIndexBuffer->Reset(cmd_list->IdxBuffer.Data,
        cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx),
        BufferType::Index,
        BufferUsage::Stream);

      for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
      {
        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

        ImVec4 clip_rect;
        clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
        clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
        clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
        clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;

        if (clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
        {
          // TODO: Fix Clip Rects

          if (pcmd->TextureId)
            (*reinterpret_cast<Ref<Texture2D>*>(pcmd->TextureId))->Bind(); // Cast from void* to Ref<Texture>
          else
            s_Data.ImGuiTexture->Bind();

          RenderCommand::SetViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
          RenderCommand::SetIndexSize(sizeof(ImDrawIdx));
          RenderCommand::SetIndexOffset(pcmd->IdxOffset * sizeof(ImDrawIdx));
          RenderCommand::SetElementCount(pcmd->ElemCount);
          RenderCommand::DrawIndexed({ s_Data.ImGuiVertexBuffer }, s_Data.ImGuiPipelineState, s_Data.ImGuiIndexBuffer);
        }
      }
    }
  }

  void ImGuiRenderer::BlockEvents(bool block)
  {
    s_Data.BlockEvents = block;
  }

  void ImGuiRenderer::OnEvent(const Scope<Event>& event)
  {
    Papaya::EventDispatcher::Dispatch<Papaya::WindowResizeEvent>(event, [&](Papaya::WindowResizeEvent* event) {
      ImGuiIO& io = ImGui::GetIO();
      io.DisplaySize.x = event->GetWidth();
      io.DisplaySize.y = event->GetHeight();
      });

    Papaya::EventDispatcher::Dispatch<Papaya::MousePressEvent>(event, [&](Papaya::MousePressEvent* event) {
      ImGuiIO& io = ImGui::GetIO();
      io.MouseDown[event->GetMouseCode() - 1] = true;
      });

    Papaya::EventDispatcher::Dispatch<Papaya::MouseReleaseEvent>(event, [&](Papaya::MouseReleaseEvent* event) {
      ImGuiIO& io = ImGui::GetIO();
      io.MouseDown[event->GetMouseCode() - 1] = false;
      });

    Papaya::EventDispatcher::Dispatch<Papaya::MouseMoveEvent>(event, [&](Papaya::MouseMoveEvent* e) {
      ImGuiIO& io = ImGui::GetIO();
      io.MousePos = ImVec2(e->GetXPosition(), e->GetYPosition());
      });

    Papaya::EventDispatcher::Dispatch<Papaya::MouseScrollEvent>(event, [&](Papaya::MouseScrollEvent* e) {
      ImGuiIO& io = ImGui::GetIO();
      io.MouseWheel += e->GetYScroll();
      io.MouseWheelH += e->GetXScroll();
      });

    Papaya::EventDispatcher::Dispatch<Papaya::KeyPressEvent>(event, [&](Papaya::KeyPressEvent* e) {
      ImGuiIO& io = ImGui::GetIO();
      io.KeysDown[e->GetKeyCode()] = true;

      int asciiCode = Input::ToASCII(e->GetKeyCode(), io.KeysDown[KeyShift]);
      io.AddInputCharacter(asciiCode);

      if (e->GetKeyCode() == Papaya::KeyControl)
        io.KeyCtrl = true;
      });

    Papaya::EventDispatcher::Dispatch<Papaya::KeyReleaseEvent>(event, [&](Papaya::KeyReleaseEvent* e) {
      ImGuiIO& io = ImGui::GetIO();
      io.KeysDown[e->GetKeyCode()] = false;

      if (e->GetKeyCode() == Papaya::KeyControl)
        io.KeyCtrl = false;
      });

    // Don't block release events
    if (event->GetEventType() != EventType::KeyRelease && event->GetEventType() != EventType::MouseRelease)
      event->Handled = s_Data.BlockEvents;
  }
} // namespace Papaya
