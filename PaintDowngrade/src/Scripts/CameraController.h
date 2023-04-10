#pragma once
#include <Engine/Scene/ScriptableEntity.h>
#include <Engine/Core/Input.h>
class CameraController : public Engine::ScriptableEntity
{
public:
	CameraController(Engine::Entity entity) : Engine::ScriptableEntity(entity) {}
	void OnCreate()
	{

	}

	void OnDestroy()
	{

	}

	void OnUpdate(Engine::Timestep ts)
	{
#if 0
		auto& translation = GetComponent<Engine::TransformComponent>().Translation;
		if (Engine::Input::IsKeyPressed(Engine::Key::A)) {
			translation.x -= m_Speed * ts * m_ZoomLevel * 0.005;
			translation.x = glm::clamp(translation.x, -m_BoundsX, m_BoundsX);
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::D)) {
			translation.x += m_Speed * ts * m_ZoomLevel * 0.005;
			translation.x = glm::clamp(translation.x, -m_BoundsX, m_BoundsX);
		}

		if (Engine::Input::IsKeyPressed(Engine::Key::S)) {
			translation.y -= m_Speed * ts * m_ZoomLevel * 0.005;
			translation.y = glm::clamp(translation.y, -m_BoundsY, m_BoundsY);
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::W)) {
			translation.y += m_Speed * ts * m_ZoomLevel * 0.005;
			translation.y = glm::clamp(translation.y, -m_BoundsY, m_BoundsY);
		}
		if (Engine::Input::IsKeyPressed(Engine::Key::Space)) {
			//EG_TRACE("Camera X:", translation.x, "Camera Y:", translation.y);
		}
#endif
		
	}

	void SetCameraSpeed(float speed)
	{
		m_Speed = speed;
	}

	void SetCameraZoomLevel(float level)
	{
		m_ZoomLevel = level;
	}

	void Move(float xOffset, float yOffset)
	{
		EG_TRACE("OFfset of camera movement X:", xOffset, "Y:", yOffset);
		auto& translation = GetComponent<Engine::TransformComponent>().Translation;
		translation.x += xOffset * m_ZoomLevel;
		translation.x = glm::clamp(translation.x, -m_BoundsX, m_BoundsX);

		translation.y -= yOffset * m_ZoomLevel;
		translation.y = glm::clamp(translation.y, -m_BoundsY, m_BoundsY);
	}

private:
	float m_Speed = 100.0f;
	float m_BoundsX = 400;
	float m_BoundsY = 225;
	float m_ZoomLevel = 180.0f;
};