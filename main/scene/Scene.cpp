#include "Scene.h"

#include "Components.h"

#include "main/renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

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
    PAPAYA_CORE_TRACE("Is registry emptied: {}", m_Registry.empty());
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

    auto& view = m_Registry.view<CameraComponent>();
    for (auto entity : view)
      m_Registry.get<CameraComponent>(entity).m_Primary = false;

    m_CameraEntity = e;
    m_CameraEntity.GetComponent<CameraComponent>().m_Primary = true;
  }

  void Scene::SetViewportSize(uint32_t width, uint32_t height)
  {
    auto& cam = m_CameraEntity.GetComponent<CameraComponent>();
    cam.Aspect = static_cast<float>(width) / static_cast<float>(height);
    PAPAYA_TRACE("TESt {}", cam.Aspect);
    cam.RefreshProjection();
  }

  void Scene::OnUpdateRuntime(Timestep ts)
  {
    PAPAYA_ASSERT(m_CameraEntity, "Scene does not have a main camera!");

    SceneCamera& camera = m_CameraEntity.GetComponent<CameraComponent>().Camera;
    auto& transform = m_CameraEntity.GetComponent<TransformComponent>();
    glm::mat4 noScaleTransform = glm::translate(glm::mat4(1.0f), transform.Translation) * glm::toMat4(glm::quat(transform.Rotation));
    Renderer2D::BeginScene(camera, noScaleTransform);

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
