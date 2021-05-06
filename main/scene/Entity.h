#pragma once

#include "Scene.h"

#include "main/core/Log.h"

#include <entt/entt.hpp>

namespace Papaya {

  class Entity {
  public:
    Entity() = default;
    Entity(Scene* scene, entt::entity entity);
    ~Entity();

    Entity(const Entity&) = default;

    template<typename T>
    bool HasComponent()
    {
      //return true;
      return m_Scene->m_Registry.any_of<T>(m_Entity);
    }

    template <typename T, typename... Args>
    T AddComponent(Args&&... args) {
      PAPAYA_ASSERT(!HasComponent<T>(), "Entity already has component of this type!");
      return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T GetComponent()
    {
      PAPAYA_ASSERT(HasComponent<T>(), "Entity doesn't have component of this type!");
      return m_Scene->m_Registry.get<T>(m_Entity);
    }

    template <typename T>
    void RemoveComponent()
    {
      PAPAYA_ASSERT(HasComponent<T>(), "Entity doesn't have component of this type!");
      m_Scene->m_Registry.remove<T>(m_Entity);
    }

  private:
    Scene* m_Scene = nullptr;
    entt::entity m_Entity{ entt::null };
  };

} // namespace Papaya