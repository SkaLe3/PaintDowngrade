#pragma once
#include <Engine/Scene/ScriptableEntity.h>
#include <Engine/Renderer/Texture.h>

enum class ActionType
{
	Cursor, Draw
};

class WorkspaceManager final :public Engine::ScriptableEntity
{
public:
	WorkspaceManager(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	virtual ~WorkspaceManager() { s_Instance = nullptr; };

	virtual void OnCreate() override;
	virtual void OnUpdate(Engine::Timestep ts) override {}

	void DrawEntity() {}
	void DestroyEntity() {}




public:
	static WorkspaceManager* Get() {
		EG_ASSERT(s_Instance, "WorkspaceManager has not been instantiated");
		return s_Instance;
	}
private:
	inline static WorkspaceManager* s_Instance = nullptr; // Singleton instance

private:
	Engine::Entity m_RootGroup;
	std::unordered_map<std::string, Engine::Ref<Engine::Texture2D>> m_Textures;

	std::vector<Engine::Entity> m_SelectedEntities;
};