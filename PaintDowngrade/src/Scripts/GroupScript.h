#pragma once
#include <Engine/Scene/ScriptableEntity.h>
#include "EntityContainer.h"

class GroupScript final : public Engine::ScriptableEntity
{
public:
	GroupScript(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}

	virtual void OnCreate() override {}
	virtual void OnUpdate(Engine::Timestep ts) override {}


	bool Has(Engine::Entity entity);
	void Add(Engine::Entity entity);
	void Remove(Engine::Entity entity);



	EntityContainer& GetEntities() { return m_Entities; }


public:
	std::vector<Engine::Entity>::iterator begin() { return m_Entities.begin(); }
	std::vector<Engine::Entity>::iterator end() { return m_Entities.end(); }
	std::vector<Engine::Entity>::reverse_iterator rbegin() { return m_Entities.rbegin(); }
	std::vector<Engine::Entity>::reverse_iterator rend() { return m_Entities.rend(); }
private:
	uint32_t m_LayerIndex = 0;
	EntityContainer m_Entities;

};