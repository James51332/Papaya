#pragma once

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

    Entity CreateEntity();
    
  private:
    entt::registry m_Registry;
  };

} // namespace Papaya