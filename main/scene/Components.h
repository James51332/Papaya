#pragma once

#include "SceneCamera.h"

#include "main/utils/String.h"

#include "main/renderer/Texture.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


namespace Papaya {

  struct TagComponent {
    String Name;

    operator String& () { return Name; }
    operator const String& () const { return Name; }

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const String& name)
      : Name(name) {}
  };

  struct TransformComponent
  {
    glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec3& translation)
      : Translation(translation) {}

    glm::mat4 GetTransform() const
    {
      glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

      return glm::translate(glm::mat4(1.0f), Translation)
        * rotation
        * glm::scale(glm::mat4(1.0f), Scale);
    }
  };

  struct SpriteRendererComponent
  {
    glm::vec4 Color;
    Ref<Texture2D> Texture;

    SpriteRendererComponent() = default;
    SpriteRendererComponent(const SpriteRendererComponent&) = default;
    SpriteRendererComponent(const glm::vec4& color)
      : Color(color), Texture(nullptr) {}
  };

  struct CameraComponent
  {
    SceneCamera Camera;
    float Zoom = 1.0f;
    float Aspect = 1.0f;

    CameraComponent()
      : Camera(Zoom * Aspect * -0.5f, Zoom * Aspect * 0.5f, Zoom * -0.5f, Zoom * 0.5f) {}
    CameraComponent(const CameraComponent&) = default;
    CameraComponent(float aspect, float zoom = 1.0f)
      : Aspect(aspect), Zoom(zoom), Camera(Zoom * Aspect * -0.5f, Zoom * Aspect * 0.5f, Zoom * -0.5f, Zoom * 0.5f) {}
    CameraComponent(float left, float right, float bottom, float top)
      : Camera(left, right, bottom, top) {}

    void RecalculateProjectionMatrix() { Camera.SetOrthographic(Zoom * Aspect * -0.5f, Zoom * Aspect * 0.5f, Zoom * -0.5f, Zoom * 0.5f); }

  private:
    friend class Scene;
  };
} // namespace Papaya