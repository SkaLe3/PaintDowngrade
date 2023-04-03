#include "WorkspaceManager.h"
#include <Engine/Scene/Components.h>
#include "Components/ShapeComponent.h"
// Usable range 0.01 - 1
void WorkspaceManager::OnCreate()
{
	m_Textures["Triangle"] = Engine::Texture2D::Create("assets/textures/Triangle.png");
	m_Textures["Circle"] = Engine::Texture2D::Create("assets/textures/Circle.png");
	m_Textures["Frame"] = Engine::Texture2D::Create("assets/textures/Frame.png");

	m_RootGroup = m_Entity.GetScene()->CreateEntity("RootGroup");
	ShapeComponent& sc = m_RootGroup.AddComponent<ShapeComponent>();
	sc.Type = ShapeType::Group;
	m_RootGroup.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.95f, 0.95f, 0.95f, 1.0f });
	Engine::TransformComponent& tc = m_RootGroup.GetComponent<Engine::TransformComponent>();

	sc.Size.x = tc.Scale.x = 800;
	sc.Size.y = tc.Scale.y = 450;
	tc.Translation.z = 0.1f;

}
