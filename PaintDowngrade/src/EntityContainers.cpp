#include "EntityContainer.h"

bool EntityContainer::Has(Engine::Entity entity)
{
	for (std::vector<Engine::Entity>::iterator it = m_Entities.begin(); it != m_Entities.end();)
	{
		if (*it == entity)
			return true;
		it++;
	}
	return false;
}

void EntityContainer::Clear()
{
	m_Entities.clear();
}

bool EntityContainer::IsEmpty()
{
	return m_Entities.empty();
}

void EntityContainer::Add(Engine::Entity entity)
{
	m_Entities.push_back(entity);
}

void EntityContainer::Remove(Engine::Entity entity)
{
	m_Entities.erase(Find(entity));
}

std::vector<Engine::Entity>::iterator EntityContainer::Find(Engine::Entity entity)
{
	std::vector<Engine::Entity>::iterator it = m_Entities.begin();
	for (; it != m_Entities.end();)
	{
		if (*it == entity)
			break;
		it++;
	}
	return it;

}
