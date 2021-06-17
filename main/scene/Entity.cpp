#include "Entity.h"

namespace Papaya {

  
  Entity::Entity(Scene* scene, entt::entity entity)
    : m_Scene(scene), m_EntityHandle(entity)
  {
  
  }
  
  Entity::~Entity()
  {
  
  }


} // namespace Papaya