#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"


CTaskMgr::CTaskMgr()
{

}

CTaskMgr::~CTaskMgr()
{

}

void CTaskMgr::tick()
{
	ClearDeadObject();

	for (size_t i = 0; i < m_vecTasks.size(); ++i)
	{
		ExecuteTask(m_vecTasks[i]);
	}

	m_vecTasks.clear();
}

void CTaskMgr::ClearDeadObject()
{
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}

	m_vecDead.clear();
}

void CTaskMgr::ExecuteTask(tTask& _Task)
{
	switch (_Task.Type)
	{
	case TASK_TYPE::SPAWN_OBJECT:
		// Param 0 : Layer Index
		// Param 1 : Object Adress
	{
		int LayerIdx = (int)_Task.dwParam_0;
		CGameObject* pSpawnObj = (CGameObject*)_Task.dwParam_1;
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(LayerIdx, pSpawnObj);
	}
		break;

	case TASK_TYPE::DESTROY_OBJECT:
		// Param 0 : Object Adress
	{
		CGameObject* pObject = (CGameObject*)_Task.dwParam_0;

		if (!pObject->IsDead())
		{
			pObject->m_Dead = true;
			m_vecDead.push_back(pObject);
		}
	}
		break;
	case TASK_TYPE::CHANGE_LEVEL:

		break;
	}	
}
