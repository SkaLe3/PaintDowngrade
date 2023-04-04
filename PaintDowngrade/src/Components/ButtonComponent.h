#pragma once

#include <glm/glm.hpp>
#include <Engine/Core/Core.h>
#include "Commands.h"

struct ButtonComponent
{
	Engine::Ref<Command> ButtonCommand = nullptr;

	ButtonComponent() = default;
	ButtonComponent(const ButtonComponent&) = default;
	ButtonComponent(Engine::Ref<Command> command) : ButtonCommand(command){}

};

