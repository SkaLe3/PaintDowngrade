#pragma once
#include <Engine/Scene/ScriptableEntity.h>

class Group final : public Engine::ScriptableEntity
{
public:
	Group(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}

	virtual void OnCreate() override {}
	virtual void OnUpdate(Engine::Timestep ts) override {}

	void Push(Engine::Entity entity);


private:
	uint32_t m_LayerIndex = 0;
	std::vector<Engine::Entity> m_Entities;

};