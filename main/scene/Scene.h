#pragma once

#include "main/core/Timestep.h"
#include "main/renderer/Camera.h"

#include "main/utils/String.h"

#include <entt/entt.hpp>

namespace Papaya {

  class Entity;

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
    void SetSceneCamera(Entity e);
    void SetViewportSize(uint32_t width, uint32_t height);

    void OnUpdate(Timestep ts, Camera& camera);
    void OnUpdateRuntime(Timestep ts);

  private:
    entt::registry m_Registry;
    entt::entity m_CameraEntity{ entt::null };
    String m_Name;
  };

} // namespace Papaya