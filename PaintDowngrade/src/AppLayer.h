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

	bool OnKeyPressed(Engine::KeyPressedEvent& e);

	void LoadScene();

private:
	Engine::Entity m_UICamera;
	Engine::Entity m_WorkspaceCamera;

	Engine::Entity m_UIPanelEntity;
	Engine::Entity m_WorkspaceEntity;

	Engine::Ref<Engine::Scene> m_ActiveScene;


};