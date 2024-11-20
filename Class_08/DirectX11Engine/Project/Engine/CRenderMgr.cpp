#include "pch.h"
#include "CRenderMgr.h"

#include "CDevice.h"
#include "CCamera.h"

CRenderMgr::CRenderMgr()
{
}

CRenderMgr::~CRenderMgr()
{
}


void CRenderMgr::init()
{
}

void CRenderMgr::tick()
{
}

void CRenderMgr::render()
{
	// Target Clear
	float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearTarget(ClearColor);

	// �� ī�޶� �����ִ� ����� ����Ÿ�ٿ� �׸���.
	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->render();
	}	
}


void CRenderMgr::RegisterCamera(CCamera* _Cam, int _Priority)
{
	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		if (m_vecCam[i] == _Cam)
		{
			if(_Priority == i)
				return;
			else
				m_vecCam[i] = nullptr;
		}
	}

	// ��ϵ� �ε��� ��ġ��ŭ ���Ͱ� Ȯ��� ��Ȳ�� �ƴϸ� ���͸� �ø���.
	if (m_vecCam.size() <= _Priority)
	{
		m_vecCam.resize(_Priority + 1);
	}
	m_vecCam[_Priority] = _Cam;
}