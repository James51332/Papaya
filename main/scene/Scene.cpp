#include "Scene.h"

#include "Entity.h"
#include "Components.h"

#include "main/renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Papaya
{

  Scene::Scene(const String& name)
    : m_Name(name)
  {
    m_CameraEntity = static_cast<entt::entity>(CreateEntity("Camera"));
    m_Registry.emplace<CameraComponent>(m_CameraEntity);
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
    m_CameraEntity = entt::null;
  }

  void Scene::OnUpdate(Timestep ts, Camera& camera)
  {
    // Basic System for rendering
    // until we flesh out more components and move this to a seperate class.

    Renderer2D::BeginScene(camera);// , glm::mat4(1.0f));

    auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
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

    auto view = m_Registry.view<CameraComponent>();
    for (auto entity : view)
      m_Registry.get<CameraComponent>(entity).m_Primary = false;

    m_CameraEntity = static_cast<entt::entity>(e);
    m_Registry.get<CameraComponent>(m_CameraEntity).m_Primary = true;
  }

  void Scene::SetViewportSize(uint32_t width, uint32_t height)
  {
    auto& cam = m_Registry.get<CameraComponent>(m_CameraEntity);
    cam.Aspect = static_cast<float>(width) / static_cast<float>(height);
    cam.RefreshProjection();
  }

  void Scene::OnUpdateRuntime(Timestep ts)
  {
    if (!m_Registry.valid(m_CameraEntity))
    {
      PAPAYA_ASSERT(false, "Scene does not have a main camera!");
      return;
    }

    SceneCamera& camera = m_Registry.get<CameraComponent>(m_CameraEntity).Camera;
    auto& transform = m_Registry.get<TransformComponent>(m_CameraEntity);
    glm::mat4 noScaleTransform = glm::translate(glm::mat4(1.0f), transform.Translation) * glm::toMat4(glm::quat(transform.Rotation));
    Renderer2D::BeginScene(camera, noScaleTransform);

    auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
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
