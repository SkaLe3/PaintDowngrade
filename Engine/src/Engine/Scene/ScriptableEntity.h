#pragma once

#include "Entity.h"
namespace Engine {

	class ScriptableEntity
	{
	public:
		ScriptableEntity(Entity entity) : m_Entity(entity) { }
		virtual ~ScriptableEntity(){}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
		Scene& GetScene()
		{
			return *m_Entity.GetScene();
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_Entity.HasComponent<T>();
		}

		Entity CreateEntity()
		{
			return GetScene().CreateEntity();
		}

		void DestroyEntity(Entity entity)
		{
			GetScene().DestroyEntity(entity);
		}
	public:
		virtual void OnCreate() {};
		virtual void OnDestroy() {};
	protected:
		virtual void OnUpdate(Timestep ts) {};
	protected:
		Entity m_Entity;
		friend class Scene;
	};

}