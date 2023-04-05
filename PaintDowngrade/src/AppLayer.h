#pragma once
#include "Engine.h"

class AppLayer : public Engine::Layer
{
public:
	AppLayer();
	virtual ~AppLayer() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Engine::Timestep ts) override;
	void OnEvent(Engine::Event& e) override;

	bool OnMouseScroll(Engine::MouseScrolledEvent& e);
	bool OnKeyPressed(Engine::KeyPressedEvent& e);
	bool OnMouseButtonPressed(Engine::MouseButtonPressedEvent& e);
	bool OnMouseButtonReleased(Engine::MouseButtonReleasedEvent& e);

	void LoadScene();

	glm::vec2 ToCameraSpace(Engine::Entity cameraEntity, const glm::vec2& coords);


private:
	Engine::Entity m_UICamera;
	Engine::Entity m_WorkspaceCamera;

	Engine::Entity m_UIPanelEntity;
	Engine::Entity m_WorkspaceEntity;

	Engine::Ref<Engine::Scene> m_ActiveScene;


};