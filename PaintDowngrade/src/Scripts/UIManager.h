#pragma once

#include <Engine/Scene/ScriptableEntity.h>
#include <Engine/Core/Log.h>

class UIManager final : public Engine::ScriptableEntity {
public:
	UIManager(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	virtual ~UIManager() { s_Instance = nullptr; };

	virtual void OnCreate() override;
	virtual void OnUpdate(Engine::Timestep ts) override {}

public:
	static UIManager* Get() {
		EG_ASSERT(s_Instance, "UIManager has not been instantiated");
		return s_Instance;
	}
private:
	inline static UIManager* s_Instance = nullptr; // Singleton instance

private:
	std::vector<Engine::Entity> m_ElementsUI;
};