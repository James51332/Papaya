#pragma once

#include "Scene.h"

#include "main/core/Log.h"

#include <entt/entt.hpp>

namespace Papaya {

  class Scene;

  class Entity {
  public:
    Entity() = default;
    Entity(Scene* scene, entt::entity entity);
    ~Entity();

    Entity(const Entity&) = default;

    void Destroy();
    bool IsActiveCamera() const;
    bool Valid() const;

    template<typename T>
    bool HasComponent()
    {
      //return true;
      return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
    }

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
      PAPAYA_ASSERT(!HasComponent<T>(), "Entity already has component of this type!");
      return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
    }

    template <typename T>
    T& GetComponent()
    {
      PAPAYA_ASSERT(HasComponent<T>(), "Entity doesn't have component of this type!");
      return m_Scene->m_Registry.get<T>(m_EntityHandle);
    }

    template <typename T>
    void RemoveComponent()
    {
      PAPAYA_ASSERT(HasComponent<T>(), "Entity doesn't have component of this type!");
      m_Scene->m_Registry.remove<T>(m_EntityHandle);
    }


    operator bool() const { return Valid(); }
    operator uint32_t() const { return static_cast<uint32_t>(m_EntityHandle); }
    operator entt::entity() const { return m_EntityHandle;  }
    bool operator==(const Entity& e) const { return m_EntityHandle == e.m_EntityHandle; }
    bool operator==(Entity& e) { return m_EntityHandle == e.m_EntityHandle; }

  private:
    Scene* m_Scene = nullptr;
    entt::entity m_EntityHandle{ entt::null };
  };

} // namespace Papaya