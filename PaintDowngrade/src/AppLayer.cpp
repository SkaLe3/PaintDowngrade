#include "AppLayer.h"


AppLayer::AppLayer()
	: Layer()
{

}

void AppLayer::OnAttach()
{
	m_ActiveScene = Engine::CreateRef<Engine::Scene>();
	m_ActiveScene->OnViewportResize(1920, 1080);


	m_UICamera = m_ActiveScene->CreateEntity("UICamera");
	m_UICamera.AddComponent<Engine::CameraComponent>();
	
	m_WorkspaceCamera = m_ActiveScene->CreateEntity("WorkspaceCamera");
	m_WorkspaceCamera.AddComponent<Engine::CameraComponent>();

}

void AppLayer::OnDetach()
{

}

void AppLayer::OnUpdate(Engine::Timestep ts)
{


	Engine::RenderCommand::SetClearColor({ 0.95f, 0.30f, 0.80f, 1.0f });
	Engine::RenderCommand::Clear();



	m_ActiveScene->OnUpdate(ts);

}

void AppLayer::OnEvent(Engine::Event& e)
{

	Engine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Engine::KeyPressedEvent>(BIND_EVENT_FN(AppLayer::OnKeyPressed));
}

bool AppLayer::OnKeyPressed(Engine::KeyPressedEvent& e)
{

	return true;
}
