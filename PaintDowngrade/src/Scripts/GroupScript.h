#pragma once
#include <Engine/Scene/ScriptableEntity.h>
#include "EntityContainer.h"
#include <Engine/Renderer/Texture.h>

class GroupScript final : public Engine::ScriptableEntity
{
public:
	GroupScript(Engine::Entity entity) : Engine::ScriptableEntity(entity)
	{
		s_EmptyTexture = Engine::Texture2D::Create("assets/textures/EmptyTexture.png");
		

		s_SelectionTexture = Engine::Texture2D::Create("assets/textures/Frame.png");
	}

	virtual void OnCreate() override {}
	virtual void OnUpdate(Engine::Timestep ts) override {}


	bool Has(Engine::Entity entity);
	void Add(Engine::Entity entity);
	void Remove(Engine::Entity entity);
	void Resize();
	Engine::Entity FindContainerWithSelection(Engine::Entity selectionEntity);
	bool CheckSelectionPresence(Engine::Entity selectionEntity);
	Engine::Entity CreateGroup(Engine::Entity selection);
	void ShipTo(Engine::Entity destinationGroupEntity, Engine::Entity selectionEntity);


	EntityContainer& GetEntities() { return m_Entities; }
	uint32_t GetCount() const;
	uint32_t GetIndex() const { return m_LayerIndex; }
	void SetIndex(uint32_t index) { m_LayerIndex = index; }
	void RefreshIndices();


public:
	std::vector<Engine::Entity>::iterator begin() { return m_Entities.begin(); }
	std::vector<Engine::Entity>::iterator end() { return m_Entities.end(); }
	std::vector<Engine::Entity>::reverse_iterator rbegin() { return m_Entities.rbegin(); }
	std::vector<Engine::Entity>::reverse_iterator rend() { return m_Entities.rend(); }
private:
	uint32_t m_LayerIndex = 0;
	EntityContainer m_Entities;
	inline static Engine::Ref<Engine::Texture2D> s_EmptyTexture = nullptr;
	inline static Engine::Ref<Engine::Texture2D> s_SelectionTexture = nullptr;


};