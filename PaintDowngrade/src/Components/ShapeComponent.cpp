#include "ShapeComponent.h"
#include "Utils.h"
#include "Scripts/GroupScript.h"

bool ShapeComponent::IsHit(const glm::vec2& coords, Engine::Ref<Engine::Entity> emptyEntity)
{
	bool flag = false;

	Engine::TransformComponent& tc = m_Entity.GetComponent<Engine::TransformComponent>();
	flag = Utils::CheckCollision(tc, coords);
	if (flag)
		if (*emptyEntity)
		{
			auto& emptytc = emptyEntity->GetComponent<Engine::TransformComponent>();
			auto& thistc = m_Entity.GetComponent<Engine::TransformComponent>();
			if (emptytc.Translation.z <= thistc.Translation.z)
				*emptyEntity = m_Entity;
		}
		else
			*emptyEntity = m_Entity;


	if (Type == ShapeType::Group)
	{ 
		GroupScript* entities = static_cast<GroupScript*>(m_Entity.GetComponent<Engine::NativeScriptComponent>().Instance);
		for (Engine::Entity entity : *entities) 
			flag |= entity.GetComponent<ShapeComponent>().IsHit(coords, emptyEntity);
	}

	return flag;
}

void ShapeComponent::Move(float x, float y)
{
	auto& tc = m_Entity.GetComponent<Engine::TransformComponent>();

	tc.Translation.x += x;
	tc.Translation.y += y;
	tc.Translation.x = tc.Translation.x;
	tc.Translation.y = tc.Translation.y;
	if (m_Entity.HasComponent<Engine::NativeScriptComponent>())
	{

		GroupScript* group = static_cast<GroupScript*>(m_Entity.GetComponent<Engine::NativeScriptComponent>().Instance);
		for (auto entity : *group)
			entity.GetComponent<ShapeComponent>().Move(x, y);
	}
}

void ShapeComponent::Resize(float x, float y, bool linked)
{
	if (linked)
	{
		x += y;
		y = x;
	}
	auto& tc = m_Entity.GetComponent<Engine::TransformComponent>();
	if (linked)
		x *= tc.Scale.x / tc.Scale.y;
	tc.Scale.x += x;
	tc.Scale.y += y;
	tc.Scale.x = glm::clamp(tc.Scale.x, 1.0f, 300.0f);
	tc.Scale.y = glm::clamp(tc.Scale.y, 1.0f, 300.0f);
	if (m_Entity.HasComponent<Engine::NativeScriptComponent>())
	{ 
		GroupScript* group = static_cast<GroupScript*>(m_Entity.GetComponent<Engine::NativeScriptComponent>().Instance);
		for (auto entity : *group)
			entity.GetComponent<ShapeComponent>().Resize(x, y, linked);
	}
}

void ShapeComponent::Destroy()
{
	if (m_Entity.HasComponent<Engine::NativeScriptComponent>())
	{
		GroupScript* group = static_cast<GroupScript*>(m_Entity.GetComponent<Engine::NativeScriptComponent>().Instance);
		for (Engine::Entity entity : *group)
			entity.GetComponent<ShapeComponent>().Destroy();

	}

	Engine::Entity entity{ m_Entity };
	entity.Destroy();


}

