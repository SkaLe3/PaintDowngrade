#pragma once

#include "entt.hpp"
#include "Engine/Core/Timestep.h"
#include "Engine/Renderer/EditorCamera.h"
#include <glm/glm.hpp>

namespace Engine {

	class Entity;
	struct CameraComponent;

	class Scene
	{
	public:
		Scene(); 
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();
		glm::vec2 GetViewportSize() { return glm::vec2{ m_ViewportWidth, m_ViewportHeiht }; }
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component) {}

		template<>
		void OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeiht = 0;

		friend class Entity;
		friend class SceneSerializer;
	};


}