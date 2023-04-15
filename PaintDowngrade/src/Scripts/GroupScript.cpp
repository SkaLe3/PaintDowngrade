#include "GroupScript.h"

bool GroupScript::Has(Engine::Entity entity)
{
	return m_Entities.Has(entity);
}

void GroupScript::Add(Engine::Entity entity)
{
	m_Entities.Add(entity);
}

void GroupScript::Remove(Engine::Entity entity)
{
	m_Entities.Remove(entity);
}
