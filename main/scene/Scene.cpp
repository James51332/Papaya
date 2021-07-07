#include "Scene.h"

#include "Entity.h"
#include "Components.h"

#include "main/renderer/Renderer2D.h"

namespace Papaya
{

  Scene::Scene(const String& name)
    : m_Name(name)
  {
  
  }

  Scene::~Scene()
  {
  
  }

  Entity Scene::CreateEntity(const String& name)
  {
    Entity e = { this, m_Registry.create() };
    e.AddComponent<TagComponent>(name);
    return e;
  }

  void Scene::Reset(const String& name)
  {
    m_Name = name;
    m_Registry.clear();
  }

  void Scene::OnUpdate(Timestep ts, OrthographicCamera& camera)
  {
    // Basic System for rendering
    // until we flesh out more components and move this to a seperate class.

    Renderer2D::BeginScene(camera);

    auto& group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
    for (auto entity : group)
    {
      auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
      Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
    }

    Renderer2D::EndScene();
  }
} // namespace Papaya
