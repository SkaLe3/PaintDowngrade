#pragma once

#include <Engine/Scene/ScriptableEntity.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/Core/Log.h>
#include "Engine/Scene/Components.h"
#include "SettingsState.h"
#include "WorkspaceManager.h"
#include <Engine/Core/KeyCodes.h>
#include "Components/ButtonComponent.h"


// додати ButtonComponent реалізувавши патерн команда
struct UIElementSpecification
{
	const char* Name = "Unnamed UI Element";
	glm::vec2 Size;
	glm::vec3 Position;

	bool isButton = true;

	glm::vec4 RealColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 OnClickColor = { 0.2f, 0.2f, 0.2f, 1.0f };

	Engine::Ref<Engine::Texture2D> RealTexture = nullptr;
	Engine::Ref<Engine::Texture2D>  OnClickTexture = nullptr;

	ToggleGroups ToggleGroup = ToggleGroups::None;
};


class ActionCommand;

class UIManager final : public Engine::ScriptableEntity 
{
public:

	UIManager(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	virtual ~UIManager() { s_Instance = nullptr; };

	virtual void OnCreate() override;
	virtual void OnUpdate(Engine::Timestep ts) override {}
	void OnMouseClick(const glm::vec2& coords);
	void OnMouseReleased();
	void OnKeyPressed(Engine::KeyCode key);

public:
	Engine::Entity CreateUIElement(const UIElementSpecification& spec);
	template<typename T, typename... Args>
	void CreateButton(Engine::Entity entity, const UIElementSpecification& spec, Args&&... args);


	void BindWorkspace(WorkspaceManager* workspace) { m_Workspace = workspace; }
	void SetCurrentState(Engine::Ref<CurrentState> state) { m_State = state; }


	float GetXSize() { return m_PanelSize; }
public:
	static UIManager* Get() {
		EG_ASSERT(s_Instance, "UIManager has not been instantiated");
		return s_Instance;
	}

private:
	inline static UIManager* s_Instance = nullptr; // Singleton instance

private:
	std::vector<Engine::Entity> m_ElementsUI;
	std::unordered_map<std::string, Engine::Ref<Engine::Texture2D>> m_Textures;
	float m_PanelSize;

	WorkspaceManager* m_Workspace = nullptr;
	Engine::Ref<CurrentState> m_State = nullptr;
};