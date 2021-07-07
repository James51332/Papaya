#pragma once

#include "main/core/Timestep.h"
#include "main/renderer/Camera.h"

#include "main/utils/String.h"

#include <entt/entt.hpp>

namespace Papaya {

  class Entity;
  class SceneHierarchyPanel;
  class SceneSerializer;

  class Scene {
    friend class Entity;
    friend class SceneHierarchyPanel;
    friend class SceneSerializer;
  public:
    Scene(const String& name = "Untitled");
    ~Scene();

    Entity CreateEntity(const String& name = "Empty Entity");

    void Reset(const String& name = "Untitled");

    const String& GetName() const { return m_Name; }
    void SetName(const String& name) { m_Name = name; }

    void OnUpdate(Timestep ts, OrthographicCamera& camera); // Eventually the camera will become a component but it can remain seperate for now
    
  private:
    entt::registry m_Registry;
    String m_Name;
  };

} // namespace Papaya