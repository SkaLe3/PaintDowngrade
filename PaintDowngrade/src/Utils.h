#pragma once
#include <glm/glm.hpp>
#include <Engine/Scene/Components.h>
class Utils
{
public:
	Utils() = delete;
	static bool CheckCollision(const Engine::TransformComponent& transform, const glm::vec2& coords)
	{
		bool left = (transform.Translation.x - (transform.Scale.x / 2.0f)) < coords.x;
		bool right = (transform.Translation.x + (transform.Scale.x / 2.0f)) > coords.x;
		bool bottom = (transform.Translation.y - (glm::abs(transform.Scale.y) / 2.0f)) < coords.y;
		bool top = (transform.Translation.y + (glm::abs(transform.Scale.y) / 2.0f)) > coords.y;
		bool result = left && right && top && bottom;

		return result;
	}
};
