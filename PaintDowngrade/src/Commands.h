#pragma once
#include "Scripts/WorkspaceManager.h"
class Command
{
public:
	Command(Engine::Ref<CurrentState> state) : m_State(state) {}
	virtual void Execute() = 0;

protected:
	Engine::Ref<CurrentState> m_State;
};

class SelectCursorModeCommand : public Command
{
public:
	SelectCursorModeCommand(Engine::Ref<CurrentState> state) : Command(state) {}
	virtual void Execute()
	{
		m_State->m_Action = ActionType::Cursor;
		EG_INFO("Cursor Mode was Selected!");
	}
};

class SelectDrawModeCommand : public Command
{
public:
	SelectDrawModeCommand(Engine::Ref<CurrentState> state) : Command(state) {}
	virtual void Execute()
	{
		m_State->m_Action = ActionType::Draw;
		EG_INFO("Draw Mode was Selected!");
	}
};

class SelectRectangleCommand : public Command
{
public:
	SelectRectangleCommand(Engine::Ref<CurrentState> state) : Command(state) {}
	virtual void Execute()
	{
		m_State->m_Shape = ShapeType::Rectangle;
		m_State->m_Action = ActionType::Draw;
		EG_INFO("Draw Mode and Rectangle Shape were Selected!");
	}
};

class SelectCircleCommand : public Command
{
public:
	SelectCircleCommand(Engine::Ref<CurrentState> state) : Command(state) {}
	virtual void Execute()
	{
		m_State->m_Shape = ShapeType::Circle;
		m_State->m_Action = ActionType::Draw;
		EG_INFO("Draw Mode and Circle Shape were Selected!");
	}
};

class SelectTriangleCommand : public Command
{
public:
	SelectTriangleCommand(Engine::Ref<CurrentState> state) : Command(state) {}
	virtual void Execute()
	{
		m_State->m_Shape = ShapeType::Triangle;
		m_State->m_Action = ActionType::Draw;
		EG_INFO("Draw Mode and Triangle Shape were Selected!");
	}
};


