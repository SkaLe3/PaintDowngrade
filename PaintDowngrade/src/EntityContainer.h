#pragma once
#include <Engine/Scene/Entity.h>

class EntityContainer
{
public:
	bool Has(Engine::Entity entity);
	void Clear();
	bool IsEmpty();
	void Add(Engine::Entity entity);
	void Remove(Engine::Entity entity);
	std::vector<Engine::Entity>& Get() { return m_Entities; }
	operator std::vector<Engine::Entity>() { return m_Entities; }

	size_t GetCount() const { return m_Entities.size(); }

public:
	std::vector<Engine::Entity>::iterator begin() { return m_Entities.begin(); }
	std::vector<Engine::Entity>::iterator end() { return m_Entities.end(); }
	std::vector<Engine::Entity>::reverse_iterator rbegin() { return m_Entities.rbegin(); }
	std::vector<Engine::Entity>::reverse_iterator rend() { return m_Entities.rend(); }
private:
	std::vector<Engine::Entity>::iterator Find(Engine::Entity entity);
private:
	std::vector<Engine::Entity> m_Entities;
};