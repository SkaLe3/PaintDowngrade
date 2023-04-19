#pragma once
#include <Engine/Scene/ScriptableEntity.h>
#include <Engine/Renderer/Texture.h>
#include "Components/ShapeComponent.h"
#include "SettingsState.h"
#include "EntityContainer.h"


class WorkspaceManager final :public Engine::ScriptableEntity
{
public:
	WorkspaceManager(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	virtual ~WorkspaceManager() { s_Instance = nullptr; };

	virtual void OnCreate() override;
	virtual void OnUpdate(Engine::Timestep ts) override;
	void OnMouseClick(const glm::vec2& coords);
	void OnMouseReleased(const glm::vec2& coords);
	void OnMouseMoved(const glm::vec2& oldCoords, const glm::vec2& newCoords, Engine::Entity camera);

	void EnableFollowCursorShape();
	void DisableFollowCursorShape();


	void DrawEntity(const glm::vec2& coords);


	void DestroyEntity();
	void Group();
	void Ungroup();
	void AddToGroup();
	void RemoveFromGroup();
	void MergeGroups();
	void Copy() {}
	void ResizeBrush(float x, float y, bool linked);
	void Resize(float x, float y, bool linked);
	void Move(float x, float y);
	void Undo() {}
	void Redo() {}
	void Clear() {}

	void Serialize() {}
	void Deserialize() {}

	glm::vec2 ToCameraSpace(const glm::vec2& coords);
	Engine::Entity Raycast(const glm::vec2& coords, Engine::Entity group);
	void Select(Engine::Entity entity);
	void Deselect(Engine::Entity entity);
	void DeselectAll();

	void ResizeGroups();


	 
	Engine::Ref<CurrentState> GetCurrentState() { return m_State; }
	Engine::Entity GetSelectionGroup() { return m_SelectionGroup; }
public:
	static WorkspaceManager* Get() {
		EG_ASSERT(s_Instance, "WorkspaceManager has not been instantiated");
		return s_Instance;
	}

private:
	inline static WorkspaceManager* s_Instance = nullptr; // Singleton instance

private:

	Engine::Entity m_RootGroup;
	Engine::Entity m_SelectionGroup;
	std::unordered_map<std::string, Engine::Ref<Engine::Texture2D>> m_Textures;

	Engine::Ref<CurrentState> m_State = Engine::CreateRef<CurrentState>();

	Engine::Entity m_FollowCursorShape;

	uint32_t m_CurrentGroupIndex = 0;
};