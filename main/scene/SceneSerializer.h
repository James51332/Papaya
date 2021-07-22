#pragma once

#include "Entity.h"
#include "Components.h"
#include "Scene.h"

namespace Papaya {

  class SceneSerializer {
  public:
    static void SerializeScene(Ref<Scene>& scene);
    static void DeserializeScene(Ref<Scene>& scene, const String& filePath);
  };

} // namespace Papaya