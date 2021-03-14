#pragma once

namespace Papaya
{

  class ImGuiRenderer
  {
  public:
    static void OnInit();
    static void Flush();
    static void OnTerminate();
  };

} // namespace Papaya
