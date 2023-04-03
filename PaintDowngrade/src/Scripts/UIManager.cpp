#include "UIManager.h"
#include <Engine/Scene/Components.h>

// Useable z range 10 - 11 
void UIManager::OnCreate()
{
	m_Textures["CursorButton"] = Engine::Texture2D::Create("assets/textures/CursorButton.png");
	m_Textures["RectangleButton"] = Engine::Texture2D::Create("assets/textures/RectangleButton.png");
	m_Textures["TriangleButton"] = Engine::Texture2D::Create("assets/textures/TriangleButton.png");
	m_Textures["CircleButton"] = Engine::Texture2D::Create("assets/textures/CircleButton.png");


	UIElementSpecification spec{ "UIPanel", {280, 720 }, { 0, 0, 10 }, {0.3, 0.3, 0.3, 1.0f} };
	CreateUIElement(spec); 

	spec.Name = "CursorButton";
	spec.Size = { 40, 40 };
	spec.Position = { 20, 20, 10.1 };
	spec.Color = { 1.0, 1.0, 1.0, 1.0 };
	CreateUIElement(spec, m_Textures["CursorButton"]);

	spec.Name = "CircleButton";
	spec.Position.x = 80;
	CreateUIElement(spec, m_Textures["CircleButton"]);

	spec.Name = "RectangleButton";
	spec.Position.x = 140;
	CreateUIElement(spec, m_Textures["RectangleButton"]);


	spec.Name = "TriangleButton";
	spec.Position.x = 200;
	CreateUIElement(spec, m_Textures["TriangleButton"]);


}

// TODO: add enum for type of UI. Button, Slider etc.
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

