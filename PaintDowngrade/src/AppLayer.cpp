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
	dispatcher.Dispatch<Engine::MouseButtonPressedEvent>(BIND_EVENT_FN(AppLayer::OnMouseButtonPressed));
	dispatcher.Dispatch<Engine::MouseButtonReleasedEvent>(BIND_EVENT_FN(AppLayer::OnMouseButtonReleased));
	dispatcher.Dispatch<Engine::MouseMovedEvent>(BIND_EVENT_FN(AppLayer::OnMouseMoved));

	dispatcher.Dispatch<Engine::WindowResizeEvent>(BIND_EVENT_FN(AppLayer::OnWindowResize));

}

bool AppLayer::OnMouseScroll(Engine::MouseScrolledEvent& e)
{

	if (Engine::Input::IsKeyPressed(Engine::Key::LeftAlt))
	{

		float delta = - e.GetYOffset() * 10;

		float value = m_WorkspaceCamera.GetComponent<Engine::CameraComponent>().Camera.GetOrthographicSize();

		m_WorkspaceCamera.GetComponent<Engine::CameraComponent>().Camera.SetOrthographicSize(glm::clamp(value + delta, 30.0f, 500.0f));
		static_cast<CameraController*>(m_WorkspaceCamera.GetComponent<Engine::NativeScriptComponent>().Instance)->SetCameraZoomLevel(value + delta);
		return true;
	}

	static_cast<CameraController*>(m_WorkspaceCamera.GetComponent<Engine::NativeScriptComponent>().Instance)->Move(e.GetXOffset() * 0.05f, e.GetYOffset()* 0.05f);
	
}

bool AppLayer::OnKeyPressed(Engine::KeyPressedEvent& e)
{
	UIManager* UI = static_cast<UIManager*>(m_UIPanelEntity.GetComponent<Engine::NativeScriptComponent>().Instance);
	UI->OnKeyPressed(e.GetKeyCode());
	return true;
}

bool AppLayer::OnMouseButtonPressed(Engine::MouseButtonPressedEvent& e)
{
	glm::vec2 ViewportSize = m_ActiveScene->GetViewportSize();

	UIManager* UI = static_cast<UIManager*>(m_UIPanelEntity.GetComponent<Engine::NativeScriptComponent>().Instance);
	WorkspaceManager * Workspace = static_cast<WorkspaceManager*>(m_WorkspaceEntity.GetComponent<Engine::NativeScriptComponent>().Instance);
	float xSize = UI->GetXSize();
	float aspectRatio = ViewportSize.x / ViewportSize.y;
	bool clickOnUI = Engine::Input::GetMouseX() / ViewportSize.x <= xSize / (720.0f * aspectRatio);
	glm::vec2 clickCoords = Engine::Input::GetMousePosition();
	glm::vec2 inRenderCoords = { clickCoords.x / ViewportSize.x * 2 - 1, clickCoords.y / ViewportSize.y * 2 - 1 };
	if (clickOnUI)
	{
		EG_TRACE("Click on UI");
		UI->OnMouseClick(ToCameraSpace(m_UICamera, inRenderCoords));
	}
	else
	{
		EG_TRACE("Click on Workspace");
		Workspace->OnMouseClick(ToCameraSpace(m_WorkspaceCamera, inRenderCoords));

	}
	return true;
}

bool AppLayer::OnMouseButtonReleased(Engine::MouseButtonReleasedEvent& e)
{
	UIManager* UI = static_cast<UIManager*>(m_UIPanelEntity.GetComponent<Engine::NativeScriptComponent>().Instance);
	UI->OnMouseReleased();
	return true;
}

bool AppLayer::OnMouseMoved(Engine::MouseMovedEvent& e)
{
	static float x = e.GetX();
	static float y = e.GetY();
	//TODO: Optimize this
	bool spacePressed = Engine::Input::IsKeyPressed(Engine::Key::Space);
	bool mousePressed = Engine::Input::IsMouseButtonPressed(Engine::Mouse::Button0);
	if (spacePressed && mousePressed)
	{

		CameraController* controller = static_cast<CameraController*>(m_WorkspaceCamera.GetComponent<Engine::NativeScriptComponent>().Instance);
		const glm::vec2& size = m_WorkspaceCamera.GetScene()->GetViewportSize();
		controller->Move((x - e.GetX())/size.x, (y - e.GetY())/size.y);

	}
	x = e.GetX();
	y = e.GetY();
	return true;
}

bool AppLayer::OnWindowResize(Engine::WindowResizeEvent& e)
{
	m_ActiveScene->OnViewportResize(e.GetWidth(), e.GetHeight());
	RecalculateUICamera(glm::vec2{ e.GetWidth(), e.GetHeight() });
	return true;
}

void AppLayer::LoadScene()
{
	m_ActiveScene = Engine::CreateRef<Engine::Scene>();
	m_ActiveScene->OnViewportResize(1920, 1080);

	// singletons "UIPanelEntity" and "WorkspaceEntity" scrips 
	// that will manage the overall UI and Workspace states.

	m_WorkspaceEntity = m_ActiveScene->CreateEntity("Workspace");
	Engine::NativeScriptComponent& nsc2 = m_WorkspaceEntity.AddComponent<Engine::NativeScriptComponent>();
	nsc2.Bind<WorkspaceManager>();
	nsc2.Instance = nsc2.InstantiateScript(m_WorkspaceEntity);
	nsc2.Instance->OnCreate();
	
	// Native scripts instantiates automatticly in Scene::OnUpdate()
	// But we need to instantiate Managers manually to get ability to work with 
	// Native Scripts before the first call of Scene::OnUpdate()

	m_UIPanelEntity = m_ActiveScene->CreateEntity("UIPanel");
	Engine::NativeScriptComponent& nsc1 = m_UIPanelEntity.AddComponent<Engine::NativeScriptComponent>();
	nsc1.Bind<UIManager>();
	nsc1.Instance = nsc1.InstantiateScript(m_UIPanelEntity);
	// Gives UIManager ref on current state of editor
	// Think about better solution
	// Need to be set before OnCreate()
	static_cast<UIManager*>(nsc1.Instance)->BindWorkspace(static_cast<WorkspaceManager*>(nsc2.Instance));
	static_cast<UIManager*>(nsc1.Instance)->SetCurrentState(static_cast<WorkspaceManager*>(nsc2.Instance)->GetCurrentState());
	nsc1.Instance->OnCreate();


	m_UICamera = m_ActiveScene->CreateEntity("UICamera");
	m_UICamera.AddComponent<Engine::CameraComponent>().Primary = false;
	RecalculateUICamera(m_ActiveScene->GetViewportSize());


	m_WorkspaceCamera = m_ActiveScene->CreateEntity("WorkspaceCamera");
	m_WorkspaceCamera.AddComponent<Engine::CameraComponent>().Primary = true;
	m_WorkspaceCamera.GetComponent<Engine::CameraComponent>().Camera.SetOrthographic(180.0f, 0.0f, 2.0f); 

	m_WorkspaceCamera.GetComponent<Engine::TransformComponent>().Translation.z = 2.0f; // range  2 - 0, use 1 - 0
	m_WorkspaceCamera.AddComponent<Engine::NativeScriptComponent>().Bind<CameraController>();
}

glm::vec2 AppLayer::ToCameraSpace(Engine::Entity cameraEntity, const glm::vec2& coords)
{
	Engine::TransformComponent& transform = cameraEntity.GetComponent<Engine::TransformComponent>();
	auto& camera = cameraEntity.GetComponent<Engine::CameraComponent>().Camera;

	glm::mat4 inverseViewProjection = transform.GetTransform() * glm::inverse(camera.GetProjection());
	glm::vec4 result = inverseViewProjection * glm::vec4{ coords.x, -coords.y, 1.0f, 1.0f };

	//EG_TRACE("Click coordinates X: ", result.x, "         Y: ", result.y);

	return glm::vec2{ result.x, result.y };
}

void AppLayer::RecalculateUICamera(const glm::vec2& viewport)
{
	float aspectRatio = viewport.x / viewport.y;
	float height = 720;
	float width = height * aspectRatio;
	m_UICamera.GetComponent<Engine::TransformComponent>().Translation = { width / 2.0f, height / 2.0f, 11.0f }; //range 11 - 9, use 11 - 10
	m_UICamera.GetComponent<Engine::TransformComponent>().Scale.y = -1.0f;
	m_UICamera.GetComponent<Engine::CameraComponent>().Camera.SetOrthographic(height, 0.0f, 2.0f);
}
