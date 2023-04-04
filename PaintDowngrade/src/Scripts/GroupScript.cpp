#include "GroupScript.h"

void Group::Push(Engine::Entity entity)
{
	m_Entities.push_back(entity);
}
