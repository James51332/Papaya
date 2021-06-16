#include "Scene.h"

#include "Entity.h"
#include "Components.h"

namespace Papaya
{

  Scene::Scene()
  {
  
  }

  Scene::~Scene()
  {
  
  }

  Entity Scene::CreateEntity()
  {
    Entity e = { this, m_Registry.create() };
    e.AddComponent<TagComponent>("Empty Entity");
    return e;
  }

} // namespace Papaya
