#pragma once

#include <entt/entt.hpp>

namespace Papaya {

  class Entity;

  class Scene {
    friend class Entity;
  public:
    Scene();
    ~Scene();

    Entity CreateEntity();
    
  private:
    entt::registry m_Registry;
  };

} // namespace Papaya