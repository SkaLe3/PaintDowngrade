#pragma once

#include <Engine/Scene/ScriptableEntity.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/Core/Log.h>

struct UIElementSpecification
{
	const char* Name = "Unnamed UI Element";
	glm::vec2 Size;
	glm::vec3 Position;
	//Engine::Texture2D Texture;
	glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
	bool isButton = true;
};

class UIManager final : public Engine::ScriptableEntity {
public:
	UIManager(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	virtual ~UIManager() { s_Instance = nullptr; };

	virtual void OnCreate() override;
	virtual void OnUpdate(Engine::Timestep ts) override {}

	Engine::Entity CreateUIElement(const UIElementSpecification& spec, Engine::Ref<Engine::Texture2D> texture = nullptr);

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
};