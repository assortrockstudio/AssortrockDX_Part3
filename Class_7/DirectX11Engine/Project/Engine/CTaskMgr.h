#pragma once
#include "singleton.h"

class CTaskMgr :
    public CSingleton<CTaskMgr>
{
    SINGLE(CTaskMgr);
private:
    vector<tTask>   m_vecTasks;

public:
    void tick();

private:
    void ExecuteTask(tTask& _Task);
};

