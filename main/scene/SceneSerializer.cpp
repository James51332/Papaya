#include "papayapch.h"
#include "SceneSerializer.h"

#include "main/core/Platform.h"

#include <yaml-cpp/yaml.h>
#include <glm/glm.hpp>

namespace Papaya {

  // OPERATORS

  YAML::Emitter& operator<<(YAML::Emitter& emitter, const glm::vec3& vector) {
    return emitter << YAML::Flow << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;
  }

  YAML::Emitter& operator<<(YAML::Emitter& emitter, const glm::vec4& vector) {
    return emitter << YAML::Flow << YAML::BeginSeq << vector.x << vector.y << vector.z << vector.w << YAML::EndSeq;
  }

  YAML::Emitter& operator<<(YAML::Emitter& emitter, const String& string) {
    return emitter << string.Raw();
  }

  YAML::Emitter& operator<<(YAML::Emitter& out, Entity& entity) {
    out << YAML::BeginMap;
    out << YAML::Key << "Entity" << YAML::Value << static_cast<uint32_t>(entity);

    if (entity.HasComponent<TagComponent>()) {
      out << YAML::Key << "TagComponent" << YAML::BeginMap;
      out << YAML::Key << "Name" << YAML::Value << entity.GetComponent<TagComponent>().Name;
      out << YAML::EndMap;
    }

    if (entity.HasComponent <TransformComponent>()) {
      out << YAML::Key << "TransformComponent" << YAML::BeginMap;

      auto& transform = entity.GetComponent<TransformComponent>();
      out << YAML::Key << "Translation" << YAML::Value << transform.Translation;
      out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
      out << YAML::Key << "Scale" << YAML::Value << transform.Scale;

      out << YAML::EndMap;
    }

    if (entity.HasComponent<SpriteRendererComponent>())
    {
      out << YAML::Key << "SpriteRendererComponent" << YAML::BeginMap;
      out << YAML::Key << "Color" << YAML::Value << entity.GetComponent<SpriteRendererComponent>().Color;
      out << YAML::EndMap;
    }

    if (entity.HasComponent<CameraComponent>())
    {
      auto& cam = entity.GetComponent<CameraComponent>();
      out << YAML::Key << "CameraComponent" << YAML::BeginMap;
      out << YAML::Key << "Zoom" << cam.Zoom;
      out << YAML::Key << "Active" << entity.IsActiveCamera();
      out << YAML::EndMap;
    }

    out << YAML::EndMap;
    return out;
  }

  // IMPLEMENTATION

  void SceneSerializer::SerializeScene(Ref<Scene>& scene)
  {
    YAML::Emitter out;
    
    out << YAML::BeginMap;

    out << YAML::Key << "Scene" << YAML::Value << scene->GetName();    
    out << YAML::Key << "Entities" << YAML::BeginSeq;
    scene->m_Registry.each([&](entt::entity e) {
      Entity entity = { scene.get(), e };
      out << entity;
    });
    out << YAML::EndSeq;

    out << YAML::EndMap;

    Papaya::Platform::WriteFile(scene->GetName() + ".pscene", out.c_str());
  }

  // OPERATORS

  void operator>>(const YAML::Node& node, glm::vec3& rhs)
  {
    if (!node.IsSequence() || node.size() != 3)
      return;

    rhs.x = node[0].as<float>();
    rhs.y = node[1].as<float>();
    rhs.z = node[2].as<float>();
  }

  void operator>>(const YAML::Node& node, glm::vec4& rhs)
  {
    if (!node.IsSequence() || node.size() != 4)
      return;

    rhs.x = node[0].as<float>();
    rhs.y = node[1].as<float>();
    rhs.z = node[2].as<float>();
    rhs.w = node[3].as<float>();
  }

  void operator>>(const YAML::Node& node, Papaya::String& rhs)
  {
    rhs = node.Scalar().c_str(); // Unfortunately YAML-cpp uses std::string internally so we need this work around
  }

  // OPERATORS

  void SceneSerializer::DeserializeScene(Ref<Scene>& scene, const String& filePath)
  {
    YAML::Node data = YAML::LoadFile(filePath.Raw());

    String sceneName;
    data["Scene"] >> sceneName;
    PAPAYA_CORE_TRACE("Loading Scene: {}...", sceneName);
    scene->Reset(sceneName);

    auto entities = data["Entities"];
    if (entities)
    {
      for (auto entity : entities)
      {
        uint32_t uuid = entity["Entity"].as<uint32_t>();

        String name;
        auto tagComponent = entity["TagComponent"];
        if (tagComponent)
          tagComponent["Name"] >> name;

        PAPAYA_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

        Entity deserializedEntity = scene->CreateEntity(name);

        auto transformComponent = entity["TransformComponent"];
        if (transformComponent)
        {
          auto& tc = deserializedEntity.GetComponent<TransformComponent>();
          transformComponent["Translation"] >> tc.Translation;
          transformComponent["Rotation"] >> tc.Rotation;
          transformComponent["Scale"] >> tc.Scale;
        }

        auto spriteRendererComponent = entity["SpriteRendererComponent"];
        if (spriteRendererComponent)
        {
          auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
          spriteRendererComponent["Color"] >> src.Color;
        }

        auto cameraComponent = entity["CameraComponent"];
        if (cameraComponent)
        {
          auto& cam = deserializedEntity.AddComponent<CameraComponent>();
          cam.Zoom = cameraComponent["Zoom"].as<float>();
          
          if (cameraComponent["Active"].as<bool>())
            scene->SetSceneCamera(deserializedEntity);
        }
      }
    }
  }

} // namespace Papaya