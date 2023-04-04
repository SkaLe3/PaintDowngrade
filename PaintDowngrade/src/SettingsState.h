#pragma once
#include <glm/glm.hpp>
#include "Components/ShapeComponent.h"

enum class ActionType
{
	None = 0, Cursor, Draw
};

// Temporary
struct CurrentState
{
	CurrentState() = default;

	ActionType m_Action = ActionType::None;
	ShapeType m_Shape = ShapeType::None;
	glm::vec2 Size = { 15.0f, 15.0f };
	glm::vec4 Color = { 0.5f, 0.5f, 0.5f, 1.0f };
};