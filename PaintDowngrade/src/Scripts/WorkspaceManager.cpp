#include "WorkspaceManager.h"
#include <Engine/Scene/Components.h>
#include "Components/ShapeComponent.h"
#include "GroupScript.h"

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
	//m_Textures["Rectangle"] = Engine::Texture2D::Create(1, 1);
		//s_Data.WhiteTexture = Texture2D::Create(1, 1);
	//uint32_t whiteTextureData = 0xffffffff;
	//s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));


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

	m_State->m_Shape = ShapeType::Circle;
	DrawEntity(glm::vec2{200, 150});

}

void WorkspaceManager::OnMouseClick(const glm::vec2& coords)
{
	if (m_State->m_Action == ActionType::Draw)
		DrawEntity(coords);
}

void WorkspaceManager::DrawEntity(const glm::vec2& coords)
{


	Engine::Entity newEntity = m_Entity.GetScene()->CreateEntity(enum_to_str[(int)m_State->m_Shape]);
	auto& src = newEntity.AddComponent<Engine::SpriteRendererComponent>(m_State->Color);
	src.Texture = m_Textures[enum_to_str[(int)m_State->m_Shape]];
	auto& tc = newEntity.GetComponent<Engine::TransformComponent>();


	tc.Scale.x = m_State->Size.x;
	tc.Scale.y = m_State->Size.y;
	tc.Translation.x = coords.x;
	tc.Translation.y = coords.y;
	tc.Translation.z = 0.02f;

	newEntity.AddComponent<ShapeComponent>(m_State->m_Shape, m_State->Size, glm::vec2{ tc.Translation.x, tc.Translation.y});
	((Group*)m_RootGroup.GetComponent<Engine::NativeScriptComponent>().Instance)->Push(newEntity);


}
