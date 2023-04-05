#pragma once
#include "Scripts/WorkspaceManager.h"



// TODO: Get State from WorkspaceManager
class Command
{
public:
	Command(WorkspaceManager* workspace, Engine::Ref<CurrentState> state) :m_Workspace(workspace), m_State(state) {}
	virtual void Execute() = 0;

protected:
	WorkspaceManager* m_Workspace;
	Engine::Ref<CurrentState> m_State;
};

class SelectCursorModeCommand : public Command
{
public:
	SelectCursorModeCommand(WorkspaceManager* workspace, Engine::Ref<CurrentState> state) : Command(workspace, state) {}
	virtual void Execute()
	{
		if (m_State->m_Action != ActionType::Cursor)
			m_Workspace->DisableFollowCursorShape();

		m_State->m_Action = ActionType::Cursor;
		EG_INFO("Cursor Mode was Selected!");

	}
};

class SelectDrawModeCommand : public Command
{
public:
	SelectDrawModeCommand(WorkspaceManager* workspace, Engine::Ref<CurrentState> state) : Command(workspace, state) {}
	virtual void Execute()
	{
		m_Workspace->EnableFollowCursorShape();

		m_State->m_Action = ActionType::Draw;
		EG_INFO("Draw Mode was Selected!");

	}
};

class SelectRectangleCommand : public Command
{
public:
	SelectRectangleCommand(WorkspaceManager* workspace, Engine::Ref<CurrentState> state) : Command(workspace, state) {}
	virtual void Execute()
	{
		m_State->m_Shape = ShapeType::Rectangle;

		m_Workspace->EnableFollowCursorShape();

		m_State->m_Action = ActionType::Draw;
		EG_INFO("Draw Mode and Rectangle Shape were Selected!");
	}
};

class SelectCircleCommand : public Command
{
public:
	SelectCircleCommand(WorkspaceManager* workspace, Engine::Ref<CurrentState> state) : Command(workspace, state) {}
	virtual void Execute()
	{
		m_State->m_Shape = ShapeType::Circle;

		m_Workspace->EnableFollowCursorShape();

		m_State->m_Action = ActionType::Draw;
		EG_INFO("Draw Mode and Circle Shape were Selected!");
	}
};

class SelectTriangleCommand : public Command
{
public:
	SelectTriangleCommand(WorkspaceManager* workspace, Engine::Ref<CurrentState> state) : Command(workspace, state) {}
	virtual void Execute()
	{
		m_State->m_Shape = ShapeType::Triangle;

		m_Workspace->EnableFollowCursorShape();

		m_State->m_Action = ActionType::Draw;
		EG_INFO("Draw Mode and Triangle Shape were Selected!");
	}
};

class SelectColorCommand : public Command
{
public:
	SelectColorCommand(WorkspaceManager* workspace, Engine::Ref<CurrentState> state, const glm::vec4& color) 
		: Command(workspace, state), m_Color(color) {}

	virtual void Execute()
	{
		m_State->Color = m_Color;
	}
private:
	glm::vec4 m_Color;
};


class ChangeXsizeCommand : public Command
{
public:
	ChangeXsizeCommand(WorkspaceManager* workspace, Engine::Ref<CurrentState> state, float factor)
		: Command(workspace, state), m_Factor(factor) {}

	virtual void Execute()
	{
		m_State->Size.x += m_Factor;
		m_State->Size.x = glm::clamp(m_State->Size.x, 1.0f, 300.0f);
	}
private:
	float m_Factor;
};

class ChangeYsizeCommand : public Command
{
public:
	ChangeYsizeCommand(WorkspaceManager* workspace, Engine::Ref<CurrentState> state, float factor)
		: Command(workspace, state), m_Factor(factor) {}

	virtual void Execute()
	{
		m_State->Size.y += m_Factor;
		m_State->Size.y = glm::clamp(m_State->Size.y, 1.0f, 300.0f);
	}
private:
	float m_Factor;
};