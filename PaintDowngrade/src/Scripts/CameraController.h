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
		if (Engine::Input::IsKeyPressed(Engine::Key::A)) {
			translation.x -= m_Speed * ts;
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::D)) {
			translation.x += m_Speed * ts;
		}

		if (Engine::Input::IsKeyPressed(Engine::Key::S)) {
			translation.y -= m_Speed * ts;
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::W)) {
			translation.y += m_Speed * ts;
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::Space)) {
			EG_TRACE("Camera X:", translation.x, "Camera Y:", translation.y);
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::Up)) {
			translation.z -= 1.0f * ts;
			EG_TRACE("Camera Z:", translation.z);
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::Down)) {
			translation.z += 1.0f * ts;
			EG_TRACE("Camera Z:", translation.z);
		}
	}

	void SetCameraSpeed(float speed)
	{
		m_Speed = speed;
	}

private:
	float m_Speed = 50.0f;
};