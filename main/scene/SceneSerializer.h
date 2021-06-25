#pragma once

#include "Scene.h"
#include "Entity.h"
#include "Components.h"

#include "main/utils/Memory.h"
#include "main/utils/String.h"

namespace Papaya {

  class SceneSerializer {
  public:
    static void SerializeScene(Ref<Scene>& scene);
    static void DeserializeScene(Ref<Scene>& scene, const String& filePath);
  };

} // namespace Papaya