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
	for (size_t i = 0; i < m_vecTasks.size(); ++i)
	{
		ExecuteTask(m_vecTasks[i]);
	}
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

		break;
	case TASK_TYPE::CHANGE_LEVEL:

		break;
	}	
}
