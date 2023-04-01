#pragma once
#include <Engine/Scene/ScriptableEntity.h>

class WorkspaceManager final :public Engine::ScriptableEntity
{
public:
	WorkspaceManager(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	virtual ~WorkspaceManager() { s_Instance = nullptr; };


	virtual void OnUpdate(Engine::Timestep ts) override {}

public:
	static WorkspaceManager* Get() {
		EG_ASSERT(s_Instance, "WorkspaceManager has not been instantiated");
		return s_Instance;
	}
private:
	inline static WorkspaceManager* s_Instance = nullptr; // Singleton instance

private:
	std::vector<Engine::Entity> m_Entities;
};