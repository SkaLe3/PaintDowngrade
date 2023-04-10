#include "ShapeComponent.h"
#include "Utils.h"
#include "Scripts/GroupScript.h"

bool ShapeComponent::IsHit(const glm::vec2& coords, Engine::Ref<Engine::Entity> emptyEntity)
{
	bool flag = false;
	Engine::TransformComponent& tc = m_Entity.GetComponent<Engine::TransformComponent>();
	flag = Utils::CheckCollision(tc, coords);
	if (flag)
	{
		if (*emptyEntity)
		{
			auto& emptytc = emptyEntity->GetComponent<Engine::TransformComponent>();
			auto& thistc = m_Entity.GetComponent<Engine::TransformComponent>();
			if (emptytc.Translation.z < thistc.Translation.z)
				*emptyEntity = m_Entity;
		}
		else
			*emptyEntity = m_Entity;
	}

	if (Type == ShapeType::Group)
	{ 
		std::vector<Engine::Entity>& entities = static_cast<GroupScript*>(m_Entity.GetComponent<Engine::NativeScriptComponent>().Instance)->GetEntities();
		for (Engine::Entity entity : entities)
			flag |= entity.GetComponent<ShapeComponent>().IsHit(coords, emptyEntity);
	}

	return flag;
}

