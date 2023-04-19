#pragma once
#include "Scene.h"
#include <entt.hpp>
#include "Engine/Core/Log.h"
namespace Engine {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) //= default;
		{
			m_EntityHandle = other.m_EntityHandle;
			m_Scene = other.m_Scene;
		}
		Entity& operator=(const Entity& other)
		{
			m_EntityHandle = other.m_EntityHandle;
			m_Scene = other.m_Scene;
			return *this;
		}

		Entity& operator=(Entity&& other)
		{
			m_EntityHandle = other.m_EntityHandle;
			m_Scene = other.m_Scene;
			other.m_EntityHandle = entt::null;
			other.m_Scene = nullptr;
			return *this;
		}

		~Entity() {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			EG_ASSERT(!HasComponent<T>(), "Entity already has component"); 
			T& component =  m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			EG_ASSERT(HasComponent<T>(), "Entity does not have component");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template <typename T>
		void RemoveComponent()
		{
			EG_ASSERT(HasComponent<T>(), "Entity does not have component"); 
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		void Destroy()
		{
			EG_ASSERT((m_EntityHandle != entt::null), "Entity does not exist");
			m_Scene->DestroyEntity(*this);
			m_EntityHandle = entt::null;
		}
		Scene* GetScene()
		{
			return m_Scene;
		}

		operator bool() const { return m_EntityHandle != entt::null && m_EntityHandle != (entt::entity)355; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}
		
		bool operator!=(const Entity& other) const
		{
			return !operator==(other);
		}

	private:
		entt::entity m_EntityHandle{ entt::null };
		
		Scene* m_Scene = nullptr; //12

		 

	};
}