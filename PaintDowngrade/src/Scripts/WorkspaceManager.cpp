#include "WorkspaceManager.h"
#include <Engine/Scene/Components.h>
// Usable range 0.01 - 1
void WorkspaceManager::OnCreate()
{
	auto sheet = m_Entity.GetScene()->CreateEntity("UIPanel");
	sheet.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.95f, 0.95f, 0.95f, 1.0f });
	Engine::TransformComponent& tc = sheet.GetComponent<Engine::TransformComponent>();

	tc.Scale.x = 450;
	tc.Scale.y = 800;
	tc.Translation.z = 0.1f; 
	m_Entities.push_back(sheet);
}
