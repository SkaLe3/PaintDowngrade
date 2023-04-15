#include "UIManager.h"
#include <Engine/Scene/Components.h>
#include <Engine/Core/Input.h>

#include "Commands.h"
#include "Utils.h"

// Useable z range 10 - 11 
void UIManager::OnCreate()
{
	EG_ASSERT(m_Workspace, "Workspace pointer should be provided before UIManager::OnCreate!");
	EG_ASSERT(m_State, "Current State should be initialized before UIManager::OnCreate!");

	m_Textures["UIPanel"] = Engine::Texture2D::Create("assets/textures/Panel.png");
	m_Textures["CursorButton"] = Engine::Texture2D::Create("assets/textures/CursorButton.png");
	m_Textures["RectangleButton"] = Engine::Texture2D::Create("assets/textures/RectangleButton.png");
	m_Textures["TriangleButton"] = Engine::Texture2D::Create("assets/textures/TriangleButton.png");
	m_Textures["CircleButton"] = Engine::Texture2D::Create("assets/textures/CircleButton.png");
	m_Textures["SizeX"] = Engine::Texture2D::Create("assets/textures/sizex.png");
	m_Textures["SizeY"] = Engine::Texture2D::Create("assets/textures/sizey.png");
	m_Textures["ArrowRight"] = Engine::Texture2D::Create("assets/textures/ArrowRight.png");
	m_Textures["ArrowLeft"] = Engine::Texture2D::Create("assets/textures/ArrowLeft.png");
	m_Textures["OnClickColor"] = Engine::Texture2D::Create("assets/textures/OnClickColor.png");
	m_Textures["RealColor"] = Engine::Texture2D::Create("assets/textures/RealColor.png");

	m_Textures["GroupButton"] = Engine::Texture2D::Create("assets/textures/GroupButton.png");
	m_Textures["UngroupButton"] = Engine::Texture2D::Create("assets/textures/UngroupButton.png");
	m_Textures["AddToGroupButton"] = Engine::Texture2D::Create("assets/textures/AddToGroupButton.png");
	m_Textures["RemoveFromGroupButton"] = Engine::Texture2D::Create("assets/textures/RemoveFromGroupButton.png");
	m_Textures["MergeGroupsButton"] = Engine::Texture2D::Create("assets/textures/MergeGroupsButton.png");


	m_PanelSize = 280.0f;
	UIElementSpecification UIspec{ "UIPanel", {m_PanelSize, 720 }, { 0, 0, 10 } };
	UIspec.RealTexture = m_Textures["UIPanel"];
	CreateUIElement(UIspec);

	UIspec.Name = "CursorButton";
	UIspec.Size = { 40, 40 };
	UIspec.Position = { 20, 20, 10.1 };
	UIspec.RealTexture = m_Textures["CursorButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	UIspec.ToggleGroup = ToggleGroups::Mode;

	Engine::Entity ent = CreateUIElement(UIspec);
	CreateButton<SelectCursorModeCommand>(ent, UIspec);

	//Select Cursor as default mode
	ent.GetComponent<Engine::SpriteRendererComponent>().Color = UIspec.OnClickColor;
	SelectCursorModeCommand commandDefaultMode(m_Workspace);
	commandDefaultMode.Execute();
	


	UIspec.Name = "RectangleButton";
	UIspec.Position.x = 80;
	UIspec.RealTexture = m_Textures["RectangleButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;

	ent = CreateUIElement(UIspec);
	CreateButton<SelectRectangleCommand>(ent, UIspec);


	UIspec.Name = "CircleButton";
	UIspec.Position.x = 140;
	UIspec.RealTexture = m_Textures["CircleButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;

	ent = CreateUIElement(UIspec);
	CreateButton<SelectCircleCommand>(ent, UIspec);


	UIspec.Name = "TriangleButton";
	UIspec.Position.x = 200;
	UIspec.RealTexture = m_Textures["TriangleButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;

	ent = CreateUIElement(UIspec);
	CreateButton<SelectTriangleCommand>(ent, UIspec);


	UIspec.Name = "WhiteColor";
	UIspec.Size = { 30, 30 };
	UIspec.Position.x = 20;
	UIspec.Position.y = 630;
	UIspec.RealTexture = m_Textures["RealColor"];
	UIspec.OnClickTexture = m_Textures["OnClickColor"];
	UIspec.ToggleGroup = ToggleGroups::Color;
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);


	UIspec.Name = "BlackColor";
	UIspec.Position.x = 70;
	UIspec.RealColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);


	UIspec.Name = "RedColor";
	UIspec.Position.x = 120;
	UIspec.RealColor = { 0.85f, 0.15f, 0.15f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);

	UIspec.Name = "GreenColor";
	UIspec.Position.x = 170;
	UIspec.RealColor = { 0.15f, 0.85f, 0.15f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);

	UIspec.Name = "BlueColor";
	UIspec.Position.x = 220;
	UIspec.RealColor = { 0.15f, 0.15f, 0.85f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);

	UIspec.Name = "LightGreyColor";
	UIspec.Position.x = 20;
	UIspec.Position.y = 680;
	UIspec.RealColor = { 0.8f, 0.8f, 0.8f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);


	UIspec.Name = "DarkGreyColor";
	UIspec.Position.x = 70;
	UIspec.RealColor = { 0.4f, 0.4f, 0.4f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);

	//Select Dark grey color as default
	ent.GetComponent<Engine::SpriteRendererComponent>().Texture = UIspec.OnClickTexture;
	SelectColorCommand commandDefaultColor(m_Workspace, UIspec.RealColor);
	commandDefaultColor.Execute();

	UIspec.Name = "PurpleColor";
	UIspec.Position.x = 120;
	UIspec.RealColor = { 0.5f, 0.15f, 0.85f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);

	UIspec.Name = "YellowColor";
	UIspec.Position.x = 170;
	UIspec.RealColor = { 0.85f, 0.85f, 0.15f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);

	UIspec.Name = "CyanColor";
	UIspec.Position.x = 220;
	UIspec.RealColor = { 0.15f, 0.85f, 0.85f, 1.0f };
	UIspec.OnClickColor = UIspec.RealColor;
	ent = CreateUIElement(UIspec);
	CreateButton<SelectColorCommand>(ent, UIspec, UIspec.RealColor);

	UIspec.Name = "SizeX";
	UIspec.Position.x = 60;
	UIspec.Position.y = 80;
	UIspec.Size = { 160, 40 };
	UIspec.RealColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	UIspec.RealTexture = m_Textures["SizeX"];
	CreateUIElement(UIspec);


	UIspec.Name = "SizeY";
	UIspec.Position.y = 140;
	UIspec.RealTexture = m_Textures["SizeY"];
	CreateUIElement(UIspec);

	UIspec.Name = "XarrowLeft";
	UIspec.Position.x = 20;
	UIspec.Position.y = 85;
	UIspec.Size = { 30, 30 };
	UIspec.OnClickColor = { 0.61f, 0.57f, 0.37f, 1.0f };
	UIspec.RealTexture = m_Textures["ArrowLeft"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	UIspec.ToggleGroup = ToggleGroups::None;
	ent = CreateUIElement(UIspec);
	CreateButton<ChangeBrushSizeCommand>(ent, UIspec, -4, 0, false);

	UIspec.Name = "XarrowRight";
	UIspec.Position.x = 230;
	UIspec.RealTexture = m_Textures["ArrowRight"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	ent = CreateUIElement(UIspec);
	CreateButton<ChangeBrushSizeCommand>(ent, UIspec, 4, 0, false);


	UIspec.Name = "YarrowLeft";
	UIspec.Position.x = 20;
	UIspec.Position.y = 145;
	UIspec.RealTexture = m_Textures["ArrowLeft"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	ent = CreateUIElement(UIspec);
	CreateButton<ChangeBrushSizeCommand>(ent, UIspec, 0, -4, false);


	UIspec.Name = "YarrowRight";
	UIspec.Position.x = 230;
	UIspec.Position.y = 145;
	UIspec.RealTexture = m_Textures["ArrowRight"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	ent = CreateUIElement(UIspec);
	CreateButton<ChangeBrushSizeCommand>(ent, UIspec, 0, 4, false);


	UIspec.Name = "GroupButton";
	UIspec.Position.x = 15;
	UIspec.Position.y = 460;
	UIspec.Size = { 120, 30 };
	UIspec.RealTexture = m_Textures["GroupButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	ent = CreateUIElement(UIspec);
	CreateButton<GroupCommand>(ent, UIspec);

	UIspec.Name = "UngroupButton";
	UIspec.Position.x = 145;
	UIspec.RealTexture = m_Textures["UngroupButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	ent = CreateUIElement(UIspec);
	CreateButton<UngroupCommand>(ent, UIspec);


	UIspec.Name = "AddToGroupButton";
	UIspec.Position.x = 15;
	UIspec.Position.y += 50;
	UIspec.RealTexture = m_Textures["AddToGroupButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	ent = CreateUIElement(UIspec);
	CreateButton<AddToGroupCommand>(ent, UIspec);


	UIspec.Name = "RemoveFromGroupButton";
	UIspec.Position.x = 145;
	UIspec.RealTexture = m_Textures["RemoveFromGroupButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	ent = CreateUIElement(UIspec);
	CreateButton<RemoveFromGroupCommand>(ent, UIspec);


	UIspec.Name = "MergeGroupsButton";
	UIspec.Position.x = 15;
	UIspec.Position.y += 50;
	UIspec.RealTexture = m_Textures["MergeGroupsButton"];
	UIspec.OnClickTexture = UIspec.RealTexture;
	ent = CreateUIElement(UIspec);
	CreateButton<MergeGroupsCommand>(ent, UIspec);

}

void UIManager::OnMouseClick(const glm::vec2& coords)
{
	for (Engine::Entity entity : m_ElementsUI)
	{
		if (!entity.HasComponent<ButtonComponent>())
			continue;

		auto& transform = entity.GetComponent<Engine::TransformComponent>();
		bool result = Utils::CheckCollision(transform , coords);

		if (!result)
			continue;

		auto& bc = entity.GetComponent<ButtonComponent>();
		bc.ButtonCommand->Execute();

		switch (bc.ToggleGroup)
		{
			case ToggleGroups::Mode:
			{
				for (Engine::Entity entity : m_ElementsUI)
				{
					if (!entity.HasComponent<ButtonComponent>())
						continue;
					auto& bc2 = entity.GetComponent<ButtonComponent>();
					auto& src2 = entity.GetComponent<Engine::SpriteRendererComponent>();
					if (bc2.ToggleGroup == ToggleGroups::Mode)
						src2.Color = bc2.RealColor;
				}
				break;
			}
			case ToggleGroups::Color:
			{
				for (Engine::Entity entity : m_ElementsUI)
				{
					if (!entity.HasComponent<ButtonComponent>())
						continue;
					auto& bc2 = entity.GetComponent<ButtonComponent>();
					auto& src2 = entity.GetComponent<Engine::SpriteRendererComponent>();
					if (bc2.ToggleGroup == ToggleGroups::Color)
					{
						src2.Color = bc2.RealColor;
						src2.Texture = bc2.RealTexture;
					}
				}
				break;
			}
		}
		entity.GetComponent<Engine::SpriteRendererComponent>().Color = bc.OnClickColor;
		entity.GetComponent<Engine::SpriteRendererComponent>().Texture = bc.OnClickTexture;
		break;
	}
}


void UIManager::OnMouseReleased()
{
	for (Engine::Entity entity : m_ElementsUI)
	{
		if (!entity.HasComponent<ButtonComponent>())
			continue;

		auto& bc = entity.GetComponent<ButtonComponent>();

		if(bc.ToggleGroup == ToggleGroups::None)
		{
			auto& src = entity.GetComponent<Engine::SpriteRendererComponent>();
			src.Color = bc.RealColor;

		}

	}
}


void UIManager::OnKeyPressed(Engine::KeyCode key)
{
	// TODO: make constants
	float value = 1;
	float link = 0;

	bool shiftPressed = Engine::Input::IsKeyPressed(Engine::Key::LeftShift) || Engine::Input::IsKeyPressed(Engine::Key::RightShift);
	bool altPressed = Engine::Input::IsKeyPressed(Engine::Key::LeftAlt) || Engine::Input::IsKeyPressed(Engine::Key::RightAlt);
	bool ctrlPressed = Engine::Input::IsKeyPressed(Engine::Key::LeftControl) || Engine::Input::IsKeyPressed(Engine::Key::RightControl);

	if (shiftPressed) 
		value = 4;
	if (ctrlPressed)
		link = true;

	if (m_State->m_Action == ActionType::Draw)
		switch (key)
		{
		case Engine::Key::Left:
		{

			ChangeBrushSizeCommand command(m_Workspace, -value*2, 0, link);
			command.Execute();
			break;
		}
		case Engine::Key::Right:
		{
			ChangeBrushSizeCommand command(m_Workspace, value*2, 0, link);
			command.Execute();
			break;
		}
		case Engine::Key::Down:
		{
			ChangeBrushSizeCommand command(m_Workspace, 0, -value*2, link);
			command.Execute();
			break;
		}
		case Engine::Key::Up:
		{
			ChangeBrushSizeCommand command(m_Workspace, 0, value*2, link);
			command.Execute();
			break;
		}

		}
	else
		if (altPressed)
			switch (key)
			{
			case Engine::Key::Left:
			{

				ChangeEntitySizeCommand command(m_Workspace, -value, 0, link);
				command.Execute();
				break;
			}
			case Engine::Key::Right:
			{
				ChangeEntitySizeCommand command(m_Workspace, value, 0, link);
				command.Execute();
				break;
			}
			case Engine::Key::Down:
			{
				ChangeEntitySizeCommand command(m_Workspace, 0, -value, link);
				command.Execute();
				break;
			}
			case Engine::Key::Up:
			{
				ChangeEntitySizeCommand command(m_Workspace, 0, value, link);
				command.Execute();
				break;
			}

			}
		else
			switch (key)
			{
			case Engine::Key::Left:
			{

				ChangeSelectedPositionCommand command(m_Workspace, -value, 0);
				command.Execute();
				break;
			}
			case Engine::Key::Right:
			{
				ChangeSelectedPositionCommand command(m_Workspace, value, 0);
				command.Execute();
				break;
			}
			case Engine::Key::Down:
			{
				ChangeSelectedPositionCommand command(m_Workspace, 0, -value);
				command.Execute();
				break;
			}
			case Engine::Key::Up:
			{
				ChangeSelectedPositionCommand command(m_Workspace, 0,  value);
				command.Execute();
				break;
			}

			}
}

Engine::Entity UIManager::CreateUIElement(const UIElementSpecification& spec)
{
	auto button = m_Entity.GetScene()->CreateEntity(spec.Name);
	button.AddComponent<Engine::SpriteRendererComponent>(spec.RealColor);
	Engine::TransformComponent& tc = button.GetComponent<Engine::TransformComponent>();
	button.AddComponent<Engine::UIComponent>();
	if (spec.RealTexture)
		button.GetComponent<Engine::SpriteRendererComponent>().Texture = spec.RealTexture;


	tc.Scale.x = spec.Size.x;
	tc.Scale.y = -spec.Size.y;
	tc.Translation.x = spec.Size.x / 2.0f + spec.Position.x;
	tc.Translation.y = spec.Size.y / 2.0f + spec.Position.y;
	tc.Translation.z = spec.Position.z;
	m_ElementsUI.push_back(button);

	return button;
}

template<typename T, typename... Args>
void UIManager::CreateButton(Engine::Entity entity, const UIElementSpecification& spec, Args&&... args)
{
	{
		auto& bc = entity.AddComponent<ButtonComponent>(Engine::CreateRef<T>(m_Workspace, std::forward<Args>(args)...));
		bc.RealColor = spec.RealColor;
		bc.OnClickColor = spec.OnClickColor;
		bc.RealTexture = spec.RealTexture;
		bc.OnClickTexture = spec.OnClickTexture;
		bc.ToggleGroup = spec.ToggleGroup;
	}
}

