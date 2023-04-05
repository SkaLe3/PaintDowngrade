#include "WorkspaceManager.h"
#include <Engine/Scene/Components.h>
#include "Components/ShapeComponent.h"
#include "GroupScript.h"
#include <Engine/Core/Input.h>

#define stringify( name ) #name

static const char* enum_to_str[] = {
	stringify(None),
	stringify(Rectangle),
	stringify(Circle),
	stringify(Triangle),
	stringify(Group)
};

// Usable range 0.01 - 1
void WorkspaceManager::OnCreate()
{
	m_Textures["Triangle"] = Engine::Texture2D::Create("assets/textures/Triangle.png");
	m_Textures["Circle"] = Engine::Texture2D::Create("assets/textures/Circle.png");
	m_Textures["Frame"] = Engine::Texture2D::Create("assets/textures/Frame.png");
	m_Textures["Rectangle"] = nullptr;
	
	m_State->m_Action = ActionType::Cursor;
	m_State->m_Shape = ShapeType::Rectangle;


	m_RootGroup = m_Entity.GetScene()->CreateEntity("RootGroup");
	ShapeComponent& sc = m_RootGroup.AddComponent<ShapeComponent>();
	sc.Type = ShapeType::Group;
	m_RootGroup.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.95f, 0.95f, 0.95f, 1.0f });
	Engine::TransformComponent& tc = m_RootGroup.GetComponent<Engine::TransformComponent>();
	Engine::NativeScriptComponent& nsc = m_RootGroup.AddComponent<Engine::NativeScriptComponent>();
	nsc.Bind<Group>();
	nsc.Instance = nsc.InstantiateScript(m_RootGroup);
	nsc.Instance->OnCreate();
	sc.Size.x = tc.Scale.x = 800;
	sc.Size.y = tc.Scale.y = 450;
	tc.Translation.z = 0.01f;


}

void WorkspaceManager::OnUpdate(Engine::Timestep ts)
{

	if(m_State->m_Action == ActionType::Draw)
	{
		glm::vec2 ViewportSize = m_Entity.GetScene()->GetViewportSize();
		glm::vec2 clickCoords = Engine::Input::GetMousePosition();
		glm::vec2 inRenderCoords = { clickCoords.x / ViewportSize.x * 2 - 1, clickCoords.y / ViewportSize.y * 2 - 1 };
		glm::vec2 spaceCoords = ToCameraSpace(inRenderCoords);


		if (m_FollowCursorShape) 
		{
			auto& tc = m_FollowCursorShape.GetComponent<Engine::TransformComponent>();
			tc.Translation.x = spaceCoords.x;
			tc.Translation.y = spaceCoords.y;
			tc.Scale.x = m_State->Size.x;
			tc.Scale.y = m_State->Size.y;
			if (m_State->m_Shape == ShapeType::Circle)
				tc.Scale.y = tc.Scale.x;
			auto& src = m_FollowCursorShape.GetComponent<Engine::SpriteRendererComponent>();
			src.Color = m_State->Color;
			src.Color.w = 0.3f;
		}
	}
}

void WorkspaceManager::OnMouseClick(const glm::vec2& coords)
{
	if (m_State->m_Action == ActionType::Draw)
		DrawEntity(coords);
}

void WorkspaceManager::DrawEntity(const glm::vec2& coords)
{
	static float index = 0.00001f;

	Engine::Entity newEntity = m_Entity.GetScene()->CreateEntity(enum_to_str[(int)m_State->m_Shape]);
	auto& src = newEntity.AddComponent<Engine::SpriteRendererComponent>(m_State->Color);
	src.Texture = m_Textures[enum_to_str[(int)m_State->m_Shape]];
	auto& tc = newEntity.GetComponent<Engine::TransformComponent>();


	tc.Scale.x = m_State->Size.x;
	tc.Scale.y = m_State->Size.y;
	if (m_State->m_Shape == ShapeType::Circle)
		tc.Scale.y = tc.Scale.x;
	tc.Translation.x = coords.x;
	tc.Translation.y = coords.y;
	tc.Translation.z = 0.02f + index;

	newEntity.AddComponent<ShapeComponent>(m_State->m_Shape, m_State->Size, glm::vec2{ tc.Translation.x, tc.Translation.y});
	((Group*)m_RootGroup.GetComponent<Engine::NativeScriptComponent>().Instance)->Push(newEntity);

	DisableFollowCursorShape();
	EnableFollowCursorShape();
	index += 0.00001f;
}

void WorkspaceManager::EnableFollowCursorShape()
{
	//EG_ASSERT(!m_FollowCursorShape, "Attempt to create FollowCursorShape when it already exist!");
	if (!m_FollowCursorShape)
	{
		m_FollowCursorShape = m_Entity.GetScene()->CreateEntity("FollowCursor");
		auto& tc = m_FollowCursorShape.GetComponent<Engine::TransformComponent>();
		tc.Translation.z = 0.99f;
		auto& src = m_FollowCursorShape.AddComponent<Engine::SpriteRendererComponent>(m_State->Color);
		src.Color.w = 0.3f;
	}
	m_FollowCursorShape.GetComponent<Engine::SpriteRendererComponent>().Texture = m_Textures[enum_to_str[(int)m_State->m_Shape]];
}

void WorkspaceManager::DisableFollowCursorShape()
{
	if (m_FollowCursorShape)
		m_FollowCursorShape.Destroy();
}

glm::vec2 WorkspaceManager::ToCameraSpace(const glm::vec2& coords)
{
	Engine::Entity cameraEntity = m_Entity.GetScene()->GetPrimaryCameraEntity();
	Engine::TransformComponent& transform = cameraEntity.GetComponent<Engine::TransformComponent>();
	auto& camera = cameraEntity.GetComponent<Engine::CameraComponent>().Camera;

	glm::mat4 inverseViewProjection = transform.GetTransform() * glm::inverse(camera.GetProjection());
	glm::vec4 result = inverseViewProjection * glm::vec4{ coords.x, -coords.y, 1.0f, 1.0f };

	//EG_TRACE("Click coordinates X: ", result.x, "         Y: ", result.y);

	return glm::vec2{ result.x, result.y };
}
