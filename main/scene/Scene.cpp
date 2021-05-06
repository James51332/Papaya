#include "Scene.h"

#include "Entity.h"

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
    return { this, m_Registry.create() };
  }

} // namespace Papaya