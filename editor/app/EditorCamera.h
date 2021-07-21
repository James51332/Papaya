#pragma once

#include "main/core/Timestep.h"
#include "main/renderer/Camera.h"

#include <glm/glm.hpp>

namespace Papaya
{

  class EditorCamera : public Camera
  {
  public:
    EditorCamera(float fov = 70.0f, float aspect = 1.0f, float nearClip = 0.1f, float farClip = 1000.0f);
    ~EditorCamera();

    void OnUpdate(Timestep ts);

    virtual void SetProjectionMatrix(const glm::mat4& projection) override {} // Disable this API for the EditorCamera
    virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjection; }

    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
    void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
    void SetFOV(float fov) { m_FOV = fov; RecalculateProjectionMatrix(); }
    void SetAspect(float aspect) { m_Aspect = aspect; RecalculateProjectionMatrix(); }
    void SetViewportSize(uint32_t width, uint32_t height) { SetAspect(static_cast<float>(width) / static_cast<float>(height)); }
    void SetClip(float nearClip, float farClip) { m_Near = nearClip; m_Far = farClip; RecalculateProjectionMatrix(); }

    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::vec3& GetRotation() const { return m_Rotation; }
    const float GetFOV() const { return m_FOV; }
    const float GetAspect() const { return m_Aspect; }
    const glm::vec2 GetClip() const { return { m_Near, m_Far }; } // This shouldn't really be used so copying isn't a problem

  private:
    void RecalculateProjectionMatrix();
    void RecalculateViewMatrix();
  private:
    glm::mat4 m_View = glm::mat4(1.0f);
    glm::mat4 m_ViewProjection = glm::mat4(1.0f);

    glm::vec3 m_Position = glm::vec3(0.0f);
    glm::vec3 m_Rotation = glm::vec3(0.0f);

    float m_FOV, m_Aspect, m_Near, m_Far;
  };

} // namespace Papaya