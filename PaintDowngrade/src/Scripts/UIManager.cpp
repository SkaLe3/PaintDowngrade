#include "UIManager.h"
#include <Engine/Scene/Components.h>
#include <Engine/Core/Input.h>
#include "Components/ButtonComponent.h"
#include "Commands.h"

// Useable z range 10 - 11 
void UIManager::OnCreate()
{
	EG_ASSERT(m_Workspace, "Workspace pointer should be provided before UIManager::OnCreate!")
	EG_ASSERT(m_State, "Current State should be initialized before UIManager::OnCreate!");

	m_Textures["CursorButton"] = Engine::Texture2D::Create("assets/textures/CursorButton.png");
	m_Textures["RectangleButton"] = Engine::Texture2D::Create("assets/textures/RectangleButton.png");
	m_Textures["TriangleButton"] = Engine::Texture2D::Create("assets/textures/TriangleButton.png");
	m_Textures["CircleButton"] = Engine::Texture2D::Create("assets/textures/CircleButton.png");
	m_Textures["SizeX"] = Engine::Texture2D::Create("assets/textures/sizex.png");
	m_Textures["SizeY"] = Engine::Texture2D::Create("assets/textures/sizey.png");
	m_Textures["ArrowRight"] = Engine::Texture2D::Create("assets/textures/ArrowRight.png");
	m_Textures["ArrowLeft"] = Engine::Texture2D::Create("assets/textures/ArrowLeft.png");


	m_PanelSize = 280.0f;
	UIElementSpecification spec{ "UIPanel", {m_PanelSize, 720 }, { 0, 0, 10 }, {0.3, 0.3, 0.3, 1.0f} };
	CreateUIElement(spec); 

	spec.Name = "CursorButton";
	spec.Size = { 40, 40 };
	spec.Position = { 20, 20, 10.1 };
	spec.Color = { 1.0, 1.0, 1.0, 1.0 };
	Engine::Entity ent = CreateUIElement(spec, m_Textures["CursorButton"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectCursorModeCommand>(m_Workspace, m_State));


	spec.Name = "RectangleButton";
	spec.Position.x = 80;
	ent = CreateUIElement(spec, m_Textures["RectangleButton"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectRectangleCommand>(m_Workspace, m_State));

	spec.Name = "CircleButton";
	spec.Position.x = 140;
	ent = CreateUIElement(spec, m_Textures["CircleButton"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectCircleCommand>(m_Workspace, m_State));

	spec.Name = "TriangleButton";
	spec.Position.x = 200;
	ent = CreateUIElement(spec, m_Textures["TriangleButton"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectTriangleCommand>(m_Workspace, m_State));

	spec.Name = "WhiteColor";
	spec.Size = { 30, 30 };
	spec.Position.x = 20;
	spec.Position.y = 630;
	spec.Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "BlackColor";
	spec.Position.x = 70;
	spec.Color = { 0.0f, 0.0f, 0.0f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "RedColor";
	spec.Position.x = 120;
	spec.Color = { 0.85f, 0.15f, 0.15f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "GreenColor";
	spec.Position.x = 170;
	spec.Color = { 0.15f, 0.85f, 0.15f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "BlueColor";
	spec.Position.x = 220;
	spec.Color = { 0.15f, 0.15f, 0.85f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "LightGreyColor";
	spec.Position.x = 20;
	spec.Position.y = 680;
	spec.Color = { 0.8f, 0.8f, 0.8f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "DarkGreyColor";
	spec.Position.x = 70;
	spec.Color = { 0.4f, 0.4f, 0.4f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "PurpleColor";
	spec.Position.x = 120;
	spec.Color = { 0.5f, 0.15f, 0.85f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "YellowColor";
	spec.Position.x = 170;
	spec.Color = { 0.85f, 0.85f, 0.15f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "CyanColor";
	spec.Position.x = 220;
	spec.Color = { 0.15f, 0.85f, 0.85f, 1.0f };
	ent = CreateUIElement(spec);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectColorCommand>(m_Workspace, m_State, spec.Color));

	spec.Name = "SizeX";
	spec.Position.x = 60;
	spec.Position.y = 80;
	spec.Size = { 160, 40 };
	spec.Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	CreateUIElement(spec, m_Textures["SizeX"]);

	spec.Name = "SizeY";
	spec.Position.y = 140;
	CreateUIElement(spec, m_Textures["SizeY"]);

	spec.Name = "XarrowLeft";
	spec.Position.x = 20;
	spec.Position.y = 85;
	spec.Size = { 30, 30 };
	ent = CreateUIElement(spec, m_Textures["ArrowLeft"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<ChangeXsizeCommand>(m_Workspace, m_State, -3));

	spec.Name = "XarrowRight";
	spec.Position.x = 230;
	ent = CreateUIElement(spec, m_Textures["ArrowRight"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<ChangeXsizeCommand>(m_Workspace, m_State, 3));

	spec.Name = "YarrowLeft";
	spec.Position.x = 20;
	spec.Position.y = 145;
	ent = CreateUIElement(spec, m_Textures["ArrowLeft"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<ChangeYsizeCommand>(m_Workspace, m_State, -3));

	spec.Name = "YarrowRight";
	spec.Position.x = 230;
	spec.Position.y = 145;
	ent = CreateUIElement(spec, m_Textures["ArrowRight"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<ChangeYsizeCommand>(m_Workspace, m_State, 3));

}

void UIManager::OnMouseClick(const glm::vec2& coords)
{
	for (Engine::Entity entity : m_ElementsUI)
	{
		if (!entity.HasComponent<ButtonComponent>())
			continue;

		auto& transform = entity.GetComponent<Engine::TransformComponent>();
		bool result = CheckCollision(transform , coords);

		if (!result)
			continue;

		entity.GetComponent<ButtonComponent>().ButtonCommand->Execute();
		break;
	}
}


void UIManager::OnKeyPressed(Engine::KeyCode key)
{
	int32_t value = 1;
	bool controlPressed = Engine::Input::IsKeyPressed(Engine::Key::LeftControl) || Engine::Input::IsKeyPressed(Engine::Key::RightControl);
	switch (key)
	{
		case Engine::Key::Left:
		{
			if (controlPressed) value = 5;
			ChangeXsizeCommand command(m_Workspace, m_State, -value);
			command.Execute();
			break;
		}
		case Engine::Key::Right:
		{
			if (controlPressed) value = 5;
			ChangeXsizeCommand command(m_Workspace, m_State, value);
			command.Execute();
			break;
		}
		case Engine::Key::Down:
		{
			if (controlPressed) value = 5;
			ChangeYsizeCommand command(m_Workspace, m_State, -value);
			command.Execute();
			break;
		}
		case Engine::Key::Up:
		{
			if (controlPressed) value = 5;
			ChangeYsizeCommand command(m_Workspace, m_State, value);
			command.Execute();
			break;
		}


	}
}

Engine::Entity UIManager::CreateUIElement(const UIElementSpecification& spec, Engine::Ref<Engine::Texture2D> texture)
{
	auto button = m_Entity.GetScene()->CreateEntity(spec.Name);
	button.AddComponent<Engine::SpriteRendererComponent>(spec.Color);
	Engine::TransformComponent& tc = button.GetComponent<Engine::TransformComponent>();
	button.AddComponent<Engine::UIComponent>();
	if (texture)
		button.GetComponent<Engine::SpriteRendererComponent>().Texture = texture;


	tc.Scale.x = spec.Size.x;
	tc.Scale.y = -spec.Size.y;
	tc.Translation.x = spec.Size.x / 2.0f + spec.Position.x;
	tc.Translation.y = spec.Size.y / 2.0f + spec.Position.y;
	tc.Translation.z = spec.Position.z;
	m_ElementsUI.push_back(button);

	return button;
}

void UIManager::SetButtonAction(Engine::Entity entity)
{

}

bool UIManager::CheckCollision(const Engine::TransformComponent& transform, const glm::vec2& coords)
{
	bool left = (transform.Translation.x - (transform.Scale.x / 2.0f)) < coords.x;
	bool right = (transform.Translation.x + (transform.Scale.x / 2.0f)) > coords.x;
	bool bottom = (transform.Translation.y - (transform.Scale.y / 2.0f) )> coords.y;
	bool top = (transform.Translation.y + (transform.Scale.y / 2.0f)) < coords.y;
	bool result = left && right && top && bottom;

	return result;
}

