#include "UIManager.h"
#include <Engine/Scene/Components.h>
#include "Components/ButtonComponent.h"
#include "Commands.h"

// Useable z range 10 - 11 
void UIManager::OnCreate()
{
	EG_ASSERT(m_State, "Current State should be initialized before OnCreate!");

	m_Textures["CursorButton"] = Engine::Texture2D::Create("assets/textures/CursorButton.png");
	m_Textures["RectangleButton"] = Engine::Texture2D::Create("assets/textures/RectangleButton.png");
	m_Textures["TriangleButton"] = Engine::Texture2D::Create("assets/textures/TriangleButton.png");
	m_Textures["CircleButton"] = Engine::Texture2D::Create("assets/textures/CircleButton.png");


	m_PanelSize = 280.0f;
	UIElementSpecification spec{ "UIPanel", {m_PanelSize, 720 }, { 0, 0, 10 }, {0.3, 0.3, 0.3, 1.0f} };
	CreateUIElement(spec); 

	spec.Name = "CursorButton";
	spec.Size = { 40, 40 };
	spec.Position = { 20, 20, 10.1 };
	spec.Color = { 1.0, 1.0, 1.0, 1.0 };
	Engine::Entity ent = CreateUIElement(spec, m_Textures["CursorButton"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectCursorModeCommand>(m_State));


	spec.Name = "RectangleButton";
	spec.Position.x = 80;
	ent = CreateUIElement(spec, m_Textures["RectangleButton"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectRectangleCommand>(m_State));

	spec.Name = "CircleButton";
	spec.Position.x = 140;
	ent = CreateUIElement(spec, m_Textures["CircleButton"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectCircleCommand>(m_State));

	spec.Name = "TriangleButton";
	spec.Position.x = 200;
	ent = CreateUIElement(spec, m_Textures["TriangleButton"]);
	ent.AddComponent<ButtonComponent>(Engine::CreateRef<SelectTriangleCommand>(m_State));


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

