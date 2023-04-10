#pragma once
#include <Engine/Scene/ScriptableEntity.h>

class GroupScript final : public Engine::ScriptableEntity
{
public:
	GroupScript(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}

	virtual void OnCreate() override {}
	virtual void OnUpdate(Engine::Timestep ts) override {}

	void Push(Engine::Entity entity);


	std::vector<Engine::Entity>& GetEntities() { return m_Entities; }


private:
	uint32_t m_LayerIndex = 0;
	std::vector<Engine::Entity> m_Entities;

};