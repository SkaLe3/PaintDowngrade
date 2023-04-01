#include "AppLayer.h"

#include "Scripts/UIManager.h"
#include "Scripts/WorkspaceManager.h"
#include "Scripts/CameraController.h"

AppLayer::AppLayer()
	: Layer()
{

}

void AppLayer::OnAttach()
{

	Engine::RenderCommand::SetClearColor({ 0.95f, 0.30f, 0.80f, 1.0f });
	LoadScene();
}

void AppLayer::OnDetach()
{

}

void AppLayer::OnUpdate(Engine::Timestep ts)
{
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

void AppLayer::LoadScene()
{
	m_ActiveScene = Engine::CreateRef<Engine::Scene>();
	m_ActiveScene->OnViewportResize(1920, 1080);

	// create and instantiate our singletons "UIPanelEntity" and "WorkspaceEntity" scrips 
	// that will manage the overall UI and Workspace states.
	Engine::Entity m_UIPanelEntity = m_ActiveScene->CreateEntity();
	m_UIPanelEntity.AddComponent<Engine::NativeScriptComponent>().Bind<UIManager>();
	m_UIPanelEntity.GetComponent<Engine::NativeScriptComponent>().InstantiateScript(m_UIPanelEntity)->OnCreate();
	// Native scripts instantiates automatticly in Scene::OnUpdate()
	// But we need to instantiate Managers manually to get ability to work with 
	// Native Scripts beforethe first call of Scene::OnUpdate()

	Engine::Entity m_WorkspaceEntity = m_ActiveScene->CreateEntity();
	m_WorkspaceEntity.AddComponent<Engine::NativeScriptComponent>().Bind<WorkspaceManager>();
	m_WorkspaceEntity.GetComponent<Engine::NativeScriptComponent>().InstantiateScript(m_WorkspaceEntity)->OnCreate();

	float height = 720;
	float width = 1280;
	m_UICamera = m_ActiveScene->CreateEntity("UICamera");
	m_UICamera.AddComponent<Engine::CameraComponent>().Primary = false;
	m_UICamera.GetComponent<Engine::CameraComponent>().Camera.SetOrthographicSize(height);
	m_UICamera.GetComponent<Engine::TransformComponent>().Translation = { width / 2.0f, height / 2.0f, 0.0f };
	m_UICamera.GetComponent<Engine::TransformComponent>().Scale.y = -1.0f;

	m_WorkspaceCamera = m_ActiveScene->CreateEntity("WorkspaceCamera");
	m_WorkspaceCamera.AddComponent<Engine::CameraComponent>();

	

	m_WorkspaceCamera.AddComponent<Engine::NativeScriptComponent>().Bind<CameraController>();
}
