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

	//Engine::RenderCommand::SetClearColor({ 0.95f, 0.30f, 0.80f, 1.0f });
	LoadScene();
}

void AppLayer::OnDetach()
{

}

void AppLayer::OnUpdate(Engine::Timestep ts)
{
	Engine::RenderCommand::SetClearColor({ 0.95f, 0.30f, 0.80f, 1.0f });
	Engine::RenderCommand::Clear();

	m_ActiveScene->OnUpdate(ts);
	//EG_INFO("Time of frame:", ts);
}

void AppLayer::OnEvent(Engine::Event& e)
{
	Engine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Engine::KeyPressedEvent>(BIND_EVENT_FN(AppLayer::OnKeyPressed));
	dispatcher.Dispatch<Engine::MouseScrolledEvent>(BIND_EVENT_FN(AppLayer::OnMouseScroll));

}

bool AppLayer::OnMouseScroll(Engine::MouseScrolledEvent& e)
{
	float delta = e.GetYOffset() * 10;
	EG_TRACE("Y offset:", e.GetYOffset(), "X offset", e.GetXOffset());
	float value = m_WorkspaceCamera.GetComponent<Engine::CameraComponent>().Camera.GetOrthographicSize();
	m_WorkspaceCamera.GetComponent<Engine::CameraComponent>().Camera.SetOrthographicSize(value + delta);
	return true;
}

bool AppLayer::OnKeyPressed(Engine::KeyPressedEvent& e)
{

	return true;
}

void AppLayer::LoadScene()
{
	m_ActiveScene = Engine::CreateRef<Engine::Scene>();
	m_ActiveScene->OnViewportResize(1920, 1080);

	// singletons "UIPanelEntity" and "WorkspaceEntity" scrips 
	// that will manage the overall UI and Workspace states.

	Engine::Entity m_UIPanelEntity = m_ActiveScene->CreateEntity("UIPanel");
	Engine::NativeScriptComponent& nsc1 = m_UIPanelEntity.AddComponent<Engine::NativeScriptComponent>();
	nsc1.Bind<UIManager>();
	nsc1.Instance = nsc1.InstantiateScript(m_UIPanelEntity);
	nsc1.Instance->OnCreate();
	
	// Native scripts instantiates automatticly in Scene::OnUpdate()
	// But we need to instantiate Managers manually to get ability to work with 
	// Native Scripts beforethe first call of Scene::OnUpdate()

	Engine::Entity m_WorkspaceEntity = m_ActiveScene->CreateEntity("Workspace");
	Engine::NativeScriptComponent& nsc2 = m_WorkspaceEntity.AddComponent<Engine::NativeScriptComponent>();
	nsc2.Bind<WorkspaceManager>();
	nsc2.Instance = nsc2.InstantiateScript(m_WorkspaceEntity);
	nsc2.Instance->OnCreate();



	float height = 720;
	float width = 1280;
	m_UICamera = m_ActiveScene->CreateEntity("UICamera");
	m_UICamera.AddComponent<Engine::CameraComponent>().Primary = false;
	m_UICamera.GetComponent<Engine::CameraComponent>().Camera.SetOrthographic(height, 0.0f, 2.0f);
	m_UICamera.GetComponent<Engine::TransformComponent>().Translation = { width / 2.0f, height / 2.0f, 11.0f }; //range 11 - 9, use 11 - 10
	m_UICamera.GetComponent<Engine::TransformComponent>().Scale.y = -1.0f;

	m_WorkspaceCamera = m_ActiveScene->CreateEntity("WorkspaceCamera");
	m_WorkspaceCamera.AddComponent<Engine::CameraComponent>().Primary = true;
	m_WorkspaceCamera.GetComponent<Engine::CameraComponent>().Camera.SetOrthographic(180.0f, 0.0f, 2.0f); 

	m_WorkspaceCamera.GetComponent<Engine::TransformComponent>().Translation.z = 2.0f; // range  2 - 0, use 1 - 0
	m_WorkspaceCamera.AddComponent<Engine::NativeScriptComponent>().Bind<CameraController>();
}
