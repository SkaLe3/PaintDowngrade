#pragma once

#include <Engine/Scene/ScriptableEntity.h>


class Group final : public Engine::ScriptableEntity
{
public:

	virtual void OnCreate() override {}
	virtual void OnUpdate(Engine::Timestep ts) override {}


private:
	uint32_t m_LayerIndex = 0;
	std::vector<Engine::Ref<Engine::Entity>> m_Entities;

}