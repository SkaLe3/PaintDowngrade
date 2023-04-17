#pragma once
#include "Scripts/WorkspaceManager.h"




class Command
{
public:
	Command(WorkspaceManager* workspace) :m_Workspace(workspace)
	{
		m_State = m_Workspace->GetCurrentState();
	}
	virtual void Execute() = 0;

protected:
	WorkspaceManager* m_Workspace;
	Engine::Ref<CurrentState> m_State;
};

class SelectCursorModeCommand : public Command
{
public:
	SelectCursorModeCommand(WorkspaceManager* workspace) : Command(workspace) {}
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
	SelectDrawModeCommand(WorkspaceManager* workspace) : Command(workspace) {}
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
	SelectRectangleCommand(WorkspaceManager* workspace) : Command(workspace) {}
	virtual void Execute()
	{
		m_State->m_Shape = ShapeType::Rectangle;

		m_Workspace->EnableFollowCursorShape();

		m_State->m_Action = ActionType::Draw;
		//m_Workspace->DeselectAll();
		EG_INFO("Draw Mode and Rectangle Shape were Selected!");
	}
};

class SelectCircleCommand : public Command
{
public:
	SelectCircleCommand(WorkspaceManager* workspace) : Command(workspace) {}
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
	SelectTriangleCommand(WorkspaceManager* workspace) : Command(workspace) {}
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
	SelectColorCommand(WorkspaceManager* workspace, const glm::vec4& color) 
		: Command(workspace), m_Color(color) {}

	virtual void Execute()
	{
		m_State->Color = m_Color;
	}
private:
	glm::vec4 m_Color;
};


class ChangeBrushSizeCommand : public Command
{
public:
	ChangeBrushSizeCommand(WorkspaceManager* workspace, float x, float y, bool linked)
		: Command(workspace), m_X(x), m_Y(y), m_Linked(linked) {}

	virtual void Execute()
	{
		m_Workspace->ResizeBrush(m_X, m_Y, m_Linked);
	}
private:
	float m_X;
	float m_Y;
	bool m_Linked;
};


class ChangeEntitySizeCommand : public Command
{
public:
	ChangeEntitySizeCommand(WorkspaceManager* workspace, float x, float y, bool linked)
		: Command(workspace), m_X(x), m_Y(y), m_Linked(linked) {}

	virtual void Execute()
	{
		m_Workspace->GetSelectionGroup().GetComponent<ShapeComponent>().Resize(m_X, m_Y, m_Linked);
		m_Workspace->ResizeGroups();
		
	}
private:
	float m_X;
	float m_Y;
	bool m_Linked;
};

class ChangeSelectedPositionCommand : public Command
{
public:
	ChangeSelectedPositionCommand(WorkspaceManager* workspace, float x, float y)
		: Command(workspace), m_X(x), m_Y(y) {}

	virtual void Execute()
	{
		m_Workspace->GetSelectionGroup().GetComponent<ShapeComponent>().Move(m_X, m_Y);
		m_Workspace->ResizeGroups();
	}
private:
	float m_X;
	float m_Y;
};


class GroupCommand : public Command
{
public:
	GroupCommand(WorkspaceManager* workspace)
		: Command(workspace) {}

	virtual void Execute()
	{
		m_Workspace->Group();
		m_Workspace->ResizeGroups();

	}

};

class UngroupCommand : public Command
{
public:
	UngroupCommand(WorkspaceManager* workspace)
		: Command(workspace) {}

	virtual void Execute()
	{
		m_Workspace->Ungroup();
	}

};

class AddToGroupCommand : public Command
{
public:
	AddToGroupCommand(WorkspaceManager* workspace)
		: Command(workspace) {}

	virtual void Execute()
	{
		m_Workspace->AddToGroup();
	}

};

class RemoveFromGroupCommand : public Command
{
public:
	RemoveFromGroupCommand(WorkspaceManager* workspace)
		: Command(workspace) {}

	virtual void Execute()
	{
		m_Workspace->RemoveFromGroup();
	}

};

class MergeGroupsCommand : public Command
{
public:
	MergeGroupsCommand(WorkspaceManager* workspace)
		: Command(workspace) {}

	virtual void Execute()
	{
		m_Workspace->MergeGroups();
	}

};