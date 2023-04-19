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

void GroupScript::RemoveRecursive(Engine::Entity selectionEntity)
{
	GroupScript* selectionGroup = static_cast<GroupScript*>(selectionEntity.GetComponent<Engine::NativeScriptComponent>().Instance);

	size_t index = 0;
	for (size_t i = 0; i < GetCount(); i++) // Empty group can't exist
	{
		Engine::Entity entity = GetEntities().Get()[index];
		for (Engine::Entity sEntity : *selectionGroup)
		if (entity == sEntity)
		{
			Remove(entity);
			break;

		}
		index++;
	}

	for (Engine::Entity entity : *this)
		if (entity.HasComponent<Engine::NativeScriptComponent>())
			static_cast<GroupScript*>(entity.GetComponent<Engine::NativeScriptComponent>().Instance)->RemoveRecursive(selectionEntity);
}

void GroupScript::Resize()
{

	for (Engine::Entity entity : *this)
		if (entity.HasComponent<Engine::NativeScriptComponent>())
			static_cast<GroupScript*>(entity.GetComponent<Engine::NativeScriptComponent>().Instance)->Resize();

	
	auto& tc = m_Entity.GetComponent<Engine::TransformComponent>();
	Engine::Entity firstEntity = m_Entities.Get()[0];
	auto& firstEntityTransform = firstEntity.GetComponent<Engine::TransformComponent>();

	glm::vec2 groupTranslation{ 0.0f, 0.0f };
	glm::vec2 groupScale{ 1.0f, 1.0f };

	glm::vec2 minPositions{ firstEntityTransform.Translation.x, firstEntityTransform.Translation.y };
	glm::vec2 maxPositions{ firstEntityTransform.Translation.x, firstEntityTransform.Translation.y };
	glm::vec2 maxScale{ firstEntityTransform.Scale.x, firstEntityTransform.Scale.y };

	for (Engine::Entity entity : *this)
	{
		auto& transform = entity.GetComponent<Engine::TransformComponent>();

		float value = (transform.Translation.x + (transform.Scale.x / 2.0f));
		if (value > maxPositions.x)
			maxPositions.x = value;

		value = (transform.Translation.y + (transform.Scale.y / 2.0f));
		if (value > maxPositions.y)
			maxPositions.y = value;
		
		value = (transform.Translation.x - (transform.Scale.x / 2.0f));
		if (value < minPositions.x)
			minPositions.x = value;

		value = (transform.Translation.y - (transform.Scale.y / 2.0f));
		if (value < minPositions.y)
			minPositions.y = value;


	}

	groupTranslation = (minPositions + maxPositions) / 2.0f;
	groupScale = glm::abs(maxPositions - minPositions) ;

	tc.Translation = { glm::round(groupTranslation.x), glm::round(groupTranslation.y), GetIndex() * 0.01f + 0.02f };
	tc.Scale = { glm::round(groupScale.x), glm::round(groupScale.y), 1.0f };
}

Engine::Entity GroupScript::FindContainerWithSelection(Engine::Entity selectionEntity)
{
	//EG_ASSERT(groupEntity.HasComponent<Engine::NativeScriptComponent>());
	Engine::Entity emptyEntity;
	bool contains = CheckSelectionPresence(selectionEntity);
	if (contains)
		return this->m_Entity;
	else
		for (Engine::Entity entity : *this)
			if (entity.HasComponent<Engine::NativeScriptComponent>())
			{
				GroupScript* group = static_cast<GroupScript*>(entity.GetComponent<Engine::NativeScriptComponent>().Instance);
				emptyEntity = group->FindContainerWithSelection(selectionEntity);
			}


	return emptyEntity;
}

bool GroupScript::CheckSelectionPresence(Engine::Entity selectionEntity)
{
	GroupScript* selection = static_cast<GroupScript*>(selectionEntity.GetComponent<Engine::NativeScriptComponent>().Instance);
	uint32_t count = selection->GetCount();
	if (selection->GetIndex() != 0)
		for (Engine::Entity entity : *selection)
		{
			glm::vec3 translation = entity.GetComponent<Engine::TransformComponent>().Translation;
			if (translation.z < 0.03f)
				--count;
		}

	for (Engine::Entity toSearchEntity : *selection)
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
	newGroup.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.0f, 0.0f, 0.0f, 0.1f }).Texture =  s_SelectionTexture;
	ShapeComponent& sc = newGroup.AddComponent<ShapeComponent>(ShapeType::Group, newGroup);

	sc.SelectionTexture = s_SelectionTexture;
	sc.DefaultTexture = s_SelectionTexture;

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


	tc.Translation = { glm::round(groupTranslation.x), glm::round(groupTranslation.y), GetIndex() * 0.01f + 0.02f };
	tc.Scale = { glm::round(groupScale.x), glm::round(groupScale.y), 1.0f };


	return newGroup;
}

void GroupScript::ShipTo(Engine::Entity destinationGroupEntity, Engine::Entity selectionEntity)
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

}

uint32_t GroupScript::GetCount() const
{
	return m_Entities.GetCount();
}

void GroupScript::RefreshIndices()
{

	for (Engine::Entity entity : *this)
	{
		glm::vec3& translation = entity.GetComponent<Engine::TransformComponent>().Translation;
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
