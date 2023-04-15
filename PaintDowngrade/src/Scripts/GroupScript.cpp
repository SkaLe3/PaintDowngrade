#include "GroupScript.h"
#include <Engine/Scene/Components.h>
#include "Components/ShapeComponent.h"
#include <Engine/Core/Log.h>

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

Engine::Entity GroupScript::FindContainer(Engine::Entity groupEntity)
{
	//EG_ASSERT(groupEntity.HasComponent<Engine::NativeScriptComponent>());
	Engine::Entity emptyEntity;
	bool contains = CheckSelectionPresence(groupEntity);
	if (contains)
		return this->m_Entity;
	else
		for (Engine::Entity entity : *this)
			if (entity.HasComponent<Engine::NativeScriptComponent>())
			{
				GroupScript* group = static_cast<GroupScript*>(entity.GetComponent<Engine::NativeScriptComponent>().Instance);
				emptyEntity = group->FindContainer(groupEntity);
			}


	return emptyEntity;
}

bool GroupScript::CheckSelectionPresence(Engine::Entity groupEntity)
{
	GroupScript* group = static_cast<GroupScript*>(groupEntity.GetComponent<Engine::NativeScriptComponent>().Instance);
	uint32_t count = group->GetCount();
	if (group->GetIndex() != 0)
		for (Engine::Entity entity : *group)
		{
			glm::vec3 translation = entity.GetComponent<Engine::TransformComponent>().Translation;
			if (translation.z < 0.03f)
				--count;
		}

	for (Engine::Entity toSearchEntity : *group)
	{
		for (Engine::Entity candidate : *this)
		{
			if (toSearchEntity == candidate)
			{ 
				--count;
				break;
			}
		}
	}
	return count == 0;
	
}

Engine::Entity GroupScript::CreateGroup(Engine::Entity selection)
{
	Engine::Entity newGroup = m_Entity.GetScene()->CreateEntity("JustGroup");
	newGroup.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f }).Texture =  s_EmptyTexture;
	ShapeComponent& sc = newGroup.AddComponent<ShapeComponent>(ShapeType::Group, newGroup);

	sc.SelectionTexture = s_SelectionTexture;
	sc.DefaultTexture = s_EmptyTexture;

	Engine::TransformComponent& tc = newGroup.GetComponent<Engine::TransformComponent>();
	Engine::NativeScriptComponent& nsc = newGroup.AddComponent<Engine::NativeScriptComponent>();

	nsc.Bind<GroupScript>();
	nsc.Instance = nsc.InstantiateScript(newGroup);
	nsc.Instance->OnCreate();


	GroupScript* selectionGroup = static_cast<GroupScript*>(selection.GetComponent<Engine::NativeScriptComponent>().Instance);
	Engine::Entity firstEntity= selectionGroup->GetEntities().Get()[0];
	auto& firstEntityTransform = firstEntity.GetComponent<Engine::TransformComponent>();
	glm::vec2 groupTranslation{0.0f, 0.0f};
	glm::vec2 groupScale{ 1.0f, 1.0f };

	glm::vec2 minPositions{ firstEntityTransform.Translation.x, firstEntityTransform.Translation.y };
	glm::vec2 maxPositions{ firstEntityTransform.Translation.x, firstEntityTransform.Translation.y };
	glm::vec2 maxScale{ firstEntityTransform.Scale.x, firstEntityTransform.Scale.y };
	for (Engine::Entity entity: *selectionGroup)
	{
		auto& transform = entity.GetComponent<Engine::TransformComponent>();
		if (transform.Translation.x > maxPositions.x)
			maxPositions.x = transform.Translation.x;
		if (transform.Translation.y > maxPositions.y)
			maxPositions.y = transform.Translation.y;
		if (transform.Translation.x < minPositions.x)
			minPositions.x = transform.Translation.x;
		if (transform.Translation.y < minPositions.y)
			minPositions.y = transform.Translation.y;

		if (transform.Scale.x > maxScale.x)
			maxScale.x = transform.Scale.x;
		if (transform.Scale.y > maxScale.y)
			maxScale.y = transform.Scale.y;

	}

	groupTranslation = (minPositions + maxPositions) / 2.0f;
	groupScale = maxScale +  glm::abs(maxPositions - groupTranslation) * 2.0f;

	tc.Translation = { groupTranslation.x, groupTranslation.y, GetIndex() * 0.01f + 0.02f };
	tc.Scale = { groupScale.x, groupScale.y, 1.0f };
	static_cast<GroupScript*>(nsc.Instance)->SetIndex(GetIndex() + 1);

	return newGroup;
}

void GroupScript::Ship(Engine::Entity destinationGroupEntity, Engine::Entity selectionEntity)
{
	GroupScript* destinationGroup = static_cast<GroupScript*>(destinationGroupEntity.GetComponent<Engine::NativeScriptComponent>().Instance);
	GroupScript* selectionGroup = static_cast<GroupScript*>(selectionEntity.GetComponent<Engine::NativeScriptComponent>().Instance);
	GroupScript* thisGroup = static_cast<GroupScript*>(this->GetComponent<Engine::NativeScriptComponent>().Instance);
	for (Engine::Entity entity : *selectionGroup)
	{
		destinationGroup->Add(entity);
	}
	for (Engine::Entity entity : *selectionGroup)
		thisGroup->Remove(entity);
	destinationGroup->SetIndex(GetIndex() + 1);
	destinationGroup->RefreshIndices();
}

uint32_t GroupScript::GetCount() const
{
	return m_Entities.GetCount();
}

void GroupScript::RefreshIndices()
{

	for (Engine::Entity entity : *this)
	{
		glm::vec3 translation = entity.GetComponent<Engine::TransformComponent>().Translation;
		uint32_t entityIndex = translation.z * 100000;
		entityIndex = entityIndex % 1000;
		translation.z = 0.02f + GetIndex() * 0.01f + entityIndex * 0.00001f;

		if (entity.HasComponent<Engine::NativeScriptComponent>())
		{
			GroupScript* group = static_cast<GroupScript*>(entity.GetComponent<Engine::NativeScriptComponent>().Instance);
			group->SetIndex(GetIndex() + 1);
			group->RefreshIndices();
		}
	}
}
