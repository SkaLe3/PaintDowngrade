#pragma once

#include <glm/glm.hpp>
#include <Engine/Core/Core.h>
#include "Commands.h"
enum class ToggleGroups
{
	None = 0, Mode, Color
};
struct ButtonComponent
{
	Engine::Ref<Command> ButtonCommand = nullptr;
	glm::vec4 OnClickColor = { 0.2f, 0.2f, 0.2f, 1.0f };
	glm::vec4 RealColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	Engine::Ref<Engine::Texture2D> OnClickTexture = nullptr;
	Engine::Ref<Engine::Texture2D> RealTexture = nullptr;

	ToggleGroups ToggleGroup = ToggleGroups::None;

	ButtonComponent() = default;
	ButtonComponent(const ButtonComponent&) = default;
	ButtonComponent(Engine::Ref<Command> command) : ButtonCommand(command){}


};

