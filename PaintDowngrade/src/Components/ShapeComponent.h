#pragma once

#include <glm/glm.hpp>
#include <Engine/Scene/Entity.h>
#include <Engine/Renderer/Texture.h>
enum class ShapeType
{
	None, Rectangle, Circle, Triangle, Group
};

struct ShapeComponent
{
	ShapeType Type = ShapeType::None;
	glm::vec2 Size { 15.0f,15.0f }; 
	glm::vec2 LocalTranslate{ 0.0f, 0.0f };


	Engine::Ref<Engine::Texture2D> SelectionTexture = nullptr;
	Engine::Ref<Engine::Texture2D> DefaultTexture = nullptr;

	ShapeComponent() = default;
	ShapeComponent(const ShapeComponent&) = default;
	ShapeComponent(ShapeType type, const glm::vec2& size, const glm::vec2& translate, Engine::Entity entity)
		: Type(type), Size(size), LocalTranslate(translate), m_Entity(entity) {}

	//Radius is x coordinate devided by 2
	//Because I don't have circle rendering yet

	bool IsHit(const glm::vec2& coords, Engine::Ref<Engine::Entity> emptyEntity);
private:
	Engine::Entity m_Entity;


};



