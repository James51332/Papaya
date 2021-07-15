#include "Scene.h"

#include "Components.h"

#include "main/renderer/Renderer2D.h"

namespace Papaya
{

  Scene::Scene(const String& name)
    : m_Name(name)
  {
    m_CameraEntity = CreateEntity("Camera");
    m_CameraEntity.AddComponent<CameraComponent>();
  }

  Scene::~Scene()
  {
  
  }

  Entity Scene::CreateEntity(const String& name)
  {
    Entity e = { this, m_Registry.create() };
    e.AddComponent<TagComponent>(name);
    e.AddComponent<TransformComponent>();
    return e;
  }

  void Scene::Reset(const String& name)
  {
    m_Registry.clear();
    m_Name = name;
    m_CameraEntity = { nullptr, entt::null };
  }

  void Scene::OnUpdate(Timestep ts, Camera& camera)
  {
    // Basic System for rendering
    // until we flesh out more components and move this to a seperate class.

    Renderer2D::BeginScene(camera);

    auto& group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
    for (auto entity : group)
    {
      auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
      if (sprite.Texture)
        Renderer2D::DrawQuad(transform.GetTransform(), sprite.Texture, 1.0f, sprite.Color);
      else
        Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
    }

    Renderer2D::EndScene();
  }

  void Scene::SetSceneCamera(Entity e)
  {
    if (!e.HasComponent<CameraComponent>())
    { 
      PAPAYA_ASSERT(false, "Entity does not have a CameraComponent!");
      return;
    }

    m_CameraEntity = e;
  }

  void Scene::OnUpdateRuntime(Timestep ts)
  {
    PAPAYA_ASSERT(m_CameraEntity, "Scene does not have a main camera!");

    SceneCamera& camera = m_CameraEntity.GetComponent<CameraComponent>().Camera;
    glm::mat4& transform = m_CameraEntity.GetComponent<TransformComponent>().GetTransform();
    Renderer2D::BeginScene(camera, transform);

    auto& group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
    for (auto entity : group)
    {
      auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
      if (sprite.Texture)
        Renderer2D::DrawQuad(transform.GetTransform(), sprite.Texture, 1.0f, sprite.Color);
      else
        Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
    }

    Renderer2D::EndScene();
  }

} // namespace Papaya
