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


