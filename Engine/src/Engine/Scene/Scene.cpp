#include "pch.h"
#include "Scene.h"
#include "Components.h"
#include "Engine/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"


namespace Engine {



	Scene::Scene()
	{


	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Default Entity" : name;

			 
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdate(Timestep ts)
	{
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{

						nsc.Instance = nsc.InstantiateScript({ entity, this });
						nsc.Instance->OnCreate();
					}
			nsc.Instance->OnUpdate(ts);
				});
		}

		Camera* mainCamera = nullptr;

		glm::mat4 mainCameraTransform;


		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				mainCamera = &camera.Camera;
				mainCameraTransform = transform.GetTransform();
				Renderer2D::BeginScene(mainCamera->GetProjection(), mainCameraTransform);

				auto view = m_Registry.view<SpriteRendererComponent>();
				uint32_t index=0;
				for (auto entity = view.rbegin(), last = view.rend(); entity != last; ++entity) 
				{
						auto [transform, sprite] = m_Registry.get<TransformComponent, SpriteRendererComponent>(*entity);
						Renderer2D::DrawSprite(transform.GetTransform(), sprite);
						
						index++;
				}
				//EG_INFO("Index = ", index, "camera:", m_Registry.get<TagComponent>(entity).Tag);

				Renderer2D::EndScene();

			}
		}
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
		}

		Renderer2D::EndScene();
	}


	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeiht = height;

		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}



	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& cc = view.get<CameraComponent>(entity);
			if (cc.Primary)
				return Entity(entity, this);
		}
		return {};
	}

	// OComponentAdded Realizations

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeiht);
	}


}