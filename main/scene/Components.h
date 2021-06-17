#pragma once

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
		// We'll add a texture to this eventually but it's not the primary concern

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};
} // namespace Papaya