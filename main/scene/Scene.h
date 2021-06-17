#pragma once

#include "main/core/Timestep.h"
#include "main/renderer/Camera.h"

#include "main/utils/String.h"

#include <entt/entt.hpp>

namespace Papaya {

  class Entity;
  class SceneHierarchyPanel;

  class Scene {
    friend class Entity;
    friend class SceneHierarchyPanel;
  public:
    Scene();
    ~Scene();

    Entity CreateEntity(const String& name = "Empty Entity");

    void OnUpdate(Timestep ts, OrthographicCamera& camera); // Eventually the camera will become a component but it can remain seperate for now
    
  private:
    entt::registry m_Registry;
  };

} // namespace Papaya