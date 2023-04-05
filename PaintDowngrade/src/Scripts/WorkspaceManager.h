#pragma once
#include <Engine/Scene/ScriptableEntity.h>
#include <Engine/Renderer/Texture.h>
#include "Components/ShapeComponent.h"
#include "SettingsState.h"


// передавання об'єктів з даними від фронтенду реалізує патерн команда
class WorkspaceManager final :public Engine::ScriptableEntity
{
public:
	WorkspaceManager(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	virtual ~WorkspaceManager() { s_Instance = nullptr; };

	virtual void OnCreate() override;
	virtual void OnUpdate(Engine::Timestep ts) override;
	void OnMouseClick(const glm::vec2& coords);

	void DrawEntity(const glm::vec2& coords);
	void DestroyEntity() {}
	void EnableFollowCursorShape();
	void DisableFollowCursorShape();

	glm::vec2 ToCameraSpace(const glm::vec2& coords);


	Engine::Ref<CurrentState> GetCurrentState() { return m_State; }
public:
	static WorkspaceManager* Get() {
		EG_ASSERT(s_Instance, "WorkspaceManager has not been instantiated");
		return s_Instance;
	}

private:
	inline static WorkspaceManager* s_Instance = nullptr; // Singleton instance

private:
	// групи реалізують патерн компонувальник
	Engine::Entity m_RootGroup;
	std::unordered_map<std::string, Engine::Ref<Engine::Texture2D>> m_Textures;

	std::vector<Engine::Entity> m_SelectedEntities;

	Engine::Ref<CurrentState> m_State = Engine::CreateRef<CurrentState>();

	Engine::Entity m_FollowCursorShape;
};