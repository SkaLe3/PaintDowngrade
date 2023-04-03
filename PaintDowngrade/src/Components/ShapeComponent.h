#pragma once

#include <glm/glm.hpp>
enum class ShapeType
{
	None, Rectangle, Circle, Triangle, Group
};

struct ShapeComponent
{
	ShapeType Type = ShapeType::None;
	glm::vec2 Size { 15.0f,15.0f }; 
	glm::vec2 LocalTranslate{ 0.0f, 0.0f };

	ShapeComponent() = default;
	ShapeComponent(const ShapeComponent&) = default;

	//Radius is x coordinate devided by 2
	//Because I don't have circle rendering yet



};



