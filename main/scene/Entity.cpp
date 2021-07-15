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


} // namespace Papaya