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
	stringify(GroupScript)
};

// Usable range 0.01 - 1
void WorkspaceManager::OnCreate()
{
	m_Textures["Triangle"] = Engine::Texture2D::Create("assets/textures/Triangle.png");
	m_Textures["Circle"] = Engine::Texture2D::Create("assets/textures/Circle.png");
	m_Textures["Rectangle"] = nullptr;
	m_Textures["Frame"] = Engine::Texture2D::Create("assets/textures/Frame.png");
	m_Textures["TriangleSelection"] = Engine::Texture2D::Create("assets/textures/TriangleSelection.png");
	m_Textures["CircleSelection"] = Engine::Texture2D::Create("assets/textures/CircleSelection.png");
	m_Textures["RectangleSelection"] = Engine::Texture2D::Create("assets/textures/RectangleSelection.png");
	
	m_State->m_Action = ActionType::Cursor;
	m_State->m_Shape = ShapeType::Rectangle;

	// Creating Sheet
	m_RootGroup = m_Entity.GetScene()->CreateEntity("RootGroup");
	ShapeComponent& sc = m_RootGroup.AddComponent<ShapeComponent>(ShapeType::Group, glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 0.0f, 0.0f }, m_RootGroup);
	m_RootGroup.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.95f, 0.95f, 0.95f, 1.0f });

	Engine::TransformComponent& tc = m_RootGroup.GetComponent<Engine::TransformComponent>();
	Engine::NativeScriptComponent& nsc = m_RootGroup.AddComponent<Engine::NativeScriptComponent>();

	nsc.Bind<GroupScript>();
	nsc.Instance = nsc.InstantiateScript(m_RootGroup);
	nsc.Instance->OnCreate();

	sc.Size.x = tc.Scale.x = 800;
	sc.Size.y = tc.Scale.y = 450;
	tc.Translation.z = 0.01f;



}

void WorkspaceManager::OnUpdate(Engine::Timestep ts)
{
	// Updating Shape that follows cursor
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
	{ 
		DrawEntity(coords);
		return;
	}
	if (m_State->m_Action == ActionType::Cursor)
	{
		Engine::Entity entity = Raycast(coords);

		if (!Engine::Input::IsKeyPressed(Engine::Key::LeftControl))
		{ 
			DeselectAll();
			m_SelectedEntities.clear();
		}

		if (entity && entity != m_RootGroup)
			Select(entity);
	}
}

void WorkspaceManager::OnMouseMoved(float xOffset, float yOffset)
{
	
}

void WorkspaceManager::DrawEntity(const glm::vec2& coords)
{
	static float index = 0.00001f;

	Engine::Entity newEntity = m_Entity.GetScene()->CreateEntity(enum_to_str[(int)m_State->m_Shape]);
	auto& src = newEntity.AddComponent<Engine::SpriteRendererComponent>(m_State->Color);

	std::string key = enum_to_str[(int)m_State->m_Shape];

	src.Texture = m_Textures[key];
	auto& tc = newEntity.GetComponent<Engine::TransformComponent>();


	tc.Scale.x = m_State->Size.x;
	tc.Scale.y = m_State->Size.y;
	if (m_State->m_Shape == ShapeType::Circle)
		tc.Scale.y = tc.Scale.x;
	tc.Translation.x = coords.x;
	tc.Translation.y = coords.y;
	tc.Translation.z = 0.02f + index;

	ShapeComponent& sc = newEntity.AddComponent<ShapeComponent>(m_State->m_Shape, m_State->Size, glm::vec2{ tc.Translation.x, tc.Translation.y}, newEntity);
	sc.DefaultTexture = src.Texture;
	sc.SelectionTexture = m_Textures[key + "Selection"];
	static_cast<GroupScript*>(m_RootGroup.GetComponent<Engine::NativeScriptComponent>().Instance)->Push(newEntity);

	DisableFollowCursorShape();
	EnableFollowCursorShape();
	index += 0.00001f;
}

void WorkspaceManager::EnableFollowCursorShape()
{
	EG_ASSERT(!m_FollowCursorShape, "Attempt to create FollowCursorShape when it already exist!");
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


	return glm::vec2{ result.x, result.y };
}

Engine::Entity WorkspaceManager::Raycast(const glm::vec2& coords)
{
	Engine::Ref<Engine::Entity> emptyEntity = Engine::CreateRef<Engine::Entity>();
	bool hit = m_RootGroup.GetComponent<ShapeComponent>().IsHit(coords, emptyEntity);
	if (hit)
		return *emptyEntity;
	return Engine::Entity();
		
}

void WorkspaceManager::Select(Engine::Entity entity)
{


	bool contains = false;
	auto& src = entity.GetComponent<Engine::SpriteRendererComponent>();
	auto& sc = entity.GetComponent<ShapeComponent>();
	for (std::vector<Engine::Entity>::iterator it = m_SelectedEntities.begin(); it != m_SelectedEntities.end();)
	{
		contains = *it == entity;
		if (contains)
		{
			EG_TRACE("Deselected Shape:	x:",
				entity.GetComponent<Engine::TransformComponent>().Translation.x, "y:",
				entity.GetComponent<Engine::TransformComponent>().Translation.y);

			m_SelectedEntities.erase(it);
			src.Texture = sc.DefaultTexture;
			src.Color.w = { 1.0f };
			src.Color -= 0.15f;
			return;
		}
		it++;
	}



	EG_TRACE("Selected Shape: x:",
		entity.GetComponent<Engine::TransformComponent>().Translation.x, "y:",
		entity.GetComponent<Engine::TransformComponent>().Translation.y);

	m_SelectedEntities.emplace_back(entity);
	src.Texture = sc.SelectionTexture;
	src.Color.w = { 0.8f };
	src.Color += 0.15f;
}

void WorkspaceManager::DeselectAll()
{
	for (auto& entity : m_SelectedEntities)
	{
		auto& src = entity.GetComponent<Engine::SpriteRendererComponent>();
		auto& sc = entity.GetComponent<ShapeComponent>();
		src.Texture = sc.DefaultTexture;
		src.Color.w = { 1.0f };
		src.Color -= 0.15f;
	}
}

// Add constants for max and min sizes;
void WorkspaceManager::ResizeBrush(float x, float y, bool linked)
{
	if (linked)
	{
		x += y;
		y = x;	
		x *= m_State->Size.x / m_State->Size.y;
	}

	m_State->Size.x += x;
	m_State->Size.x = glm::clamp(m_State->Size.x, 1.0f, 300.0f);


	m_State->Size.y += y;
	m_State->Size.y = glm::clamp(m_State->Size.y, 1.0f, 300.0f);
}

void WorkspaceManager::Resize(float x, float y, bool linked)
{
	if (linked)
	{
		x += y;
		y = x;
	}

	for (auto entity : m_SelectedEntities)
	{
		auto& tc = entity.GetComponent<Engine::TransformComponent>();
		if (linked)
		x *= tc.Scale.x / tc.Scale.y;
		tc.Scale.x += x;
		tc.Scale.y += y;
		tc.Scale.x = glm::clamp(tc.Scale.x, 1.0f, 300.0f);
		tc.Scale.y = glm::clamp(tc.Scale.y, 1.0f, 300.0f);
	}
}

void WorkspaceManager::Move(float x, float y)
{
	for (auto entity : m_SelectedEntities)
	{
		auto& tc = entity.GetComponent<Engine::TransformComponent>();

		tc.Translation.x += x;
		tc.Translation.y += y;
	}
}
