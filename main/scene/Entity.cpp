#include "papayapch.h"
#include "Entity.h"
#include "Scene.h"

namespace Papaya {

  
  Entity::Entity(Scene* scene, entt::entity entity)
    : m_Scene(scene), m_EntityHandle(entity)
  {
  
  }
  
  Entity::~Entity()
  {
  
  }

  void Entity::Destroy()
  {
    m_Scene->m_Registry.destroy(m_EntityHandle);
  }

  bool Entity::IsActiveCamera() const
  {
    return m_Scene->IsSceneCamera(*this);
  }

  bool Entity::Valid() const
  {
    if (m_Scene)
      return m_Scene->m_Registry.valid(m_EntityHandle);
    else
      return false;
  }


} // namespace Papaya