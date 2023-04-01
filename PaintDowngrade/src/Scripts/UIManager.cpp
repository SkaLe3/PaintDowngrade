#include "UIManager.h"
#include <Engine/Scene/Components.h>

void UIManager::OnCreate()
{

	{
		auto panel = m_Entity.GetScene()->CreateEntity("UIPanel");
		panel.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.3f, 0.3f, 0.3f, 1.0f });
		Engine::TransformComponent& tc = panel.GetComponent<Engine::TransformComponent>();

		tc.Scale.x = 280;
		tc.Scale.y = 720;
		tc.Translation.x = tc.Scale.x/ 2.0f;
		tc.Translation.y = tc.Scale.y / 2.0f;
		m_ElementsUI.push_back(panel);
	}
	// TODO: Make function CreateButton(const ButtonSpecification& spec);
	// 
	// struct ButtonSpecification{
	//		const char* name;
	//		float width, height;
	//		float x, y;
	//		glm::vec4 color
	// }

	{
		auto cursorButton = m_Entity.GetScene()->CreateEntity("CursorButton");
		cursorButton.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f });
		Engine::TransformComponent& tc = cursorButton.GetComponent<Engine::TransformComponent>();
		tc.Scale.x = 40;
		tc.Scale.y = 40;
		tc.Translation.x = tc.Scale.x / 2.0f + 20.0f;
		tc.Translation.y = tc.Scale.y / 2.0f + 20.0f;
		m_ElementsUI.push_back(cursorButton);
	}

	{
		auto circleButton = m_Entity.GetScene()->CreateEntity("CircleButton");
		circleButton.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f });
		Engine::TransformComponent& tc = circleButton.GetComponent<Engine::TransformComponent>();
		tc.Scale.x = 40;
		tc.Scale.y = 40;
		tc.Translation.x = tc.Scale.x / 2.0f + 80.0f;
		tc.Translation.y = tc.Scale.y / 2.0f + 20.0f;
		m_ElementsUI.push_back(circleButton);
	}

	{
		auto rectButton = m_Entity.GetScene()->CreateEntity("RectangleButton");
		rectButton.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f });
		Engine::TransformComponent& tc = rectButton.GetComponent<Engine::TransformComponent>();
		tc.Scale.x = 40;
		tc.Scale.y = 40;
		tc.Translation.x = tc.Scale.x / 2.0f + 140.0f;
		tc.Translation.y = tc.Scale.y / 2.0f + 20.0f;
		m_ElementsUI.push_back(rectButton);
	}

	{
		auto triangleButton = m_Entity.GetScene()->CreateEntity("TriangleleButton");
		triangleButton.AddComponent<Engine::SpriteRendererComponent>(glm::vec4{ 0.5f, 0.5f, 0.5f, 1.0f });
		Engine::TransformComponent& tc = triangleButton.GetComponent<Engine::TransformComponent>();
		tc.Scale.x = 40;
		tc.Scale.y = 40;
		tc.Translation.x = tc.Scale.x / 2.0f + 200.0f;
		tc.Translation.y = tc.Scale.y / 2.0f + 20.0f;
		m_ElementsUI.push_back(triangleButton);
	}


}

