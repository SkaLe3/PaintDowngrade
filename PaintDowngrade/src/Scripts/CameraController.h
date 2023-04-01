#pragma once
#include <Engine/Scene/ScriptableEntity.h>
#include <Engine/Core/Input.h>
class CameraController : public Engine::ScriptableEntity
{
public:
	CameraController(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	void OnCreate()
	{
		//GetComponent<Engine::TransformComponent>();
		std::cout << "OnCreate!" << std::endl;
	}

	void OnDestroy()
	{

	}

	void OnUpdate(Engine::Timestep ts)
	{
		auto& translation = GetComponent<Engine::TransformComponent>().Translation;
		float speed = 100.0f;
		if (Engine::Input::IsKeyPressed(Engine::Key::A)) {
			translation.x -= speed * ts;
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::D)) {
			translation.x += speed * ts;
		}

		if (Engine::Input::IsKeyPressed(Engine::Key::S)) {
			translation.y += speed * ts;
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::W)) {
			translation.y -= speed * ts;
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::Space)) {
			EG_TRACE("Camera X:", translation.x, "Camera Y:", translation.y);
		}
	}
};