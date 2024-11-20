#include "pch.h"
#include "CAnim2D.h"

#include "CDevice.h"
#include "CConstBuffer.h"

#include "CTimeMgr.h"

#include "CTexture.h"


CAnim2D::CAnim2D()
	: m_Animator(nullptr)
	, m_CurIdx(0)
	, m_Finish(false)
	, m_Time(0.f)
{
}

CAnim2D::~CAnim2D()
{
}

void CAnim2D::Create(Ptr<CTexture> _AltasTex, Vec2 _LeftTopPixelPos, Vec2 _vSlicePixelSize
					, int _FrameCount, UINT _FPS)
{
	assert(_AltasTex.Get());

	m_AtlasTex = _AltasTex;

	for (int i = 0; i < _FrameCount; ++i)
	{
		tAnim2DFrm frm = {};

		frm.LeftTop.x = (_LeftTopPixelPos.x + _vSlicePixelSize.x * i) / m_AtlasTex->GetWidth();
		frm.LeftTop.y = _LeftTopPixelPos.y / m_AtlasTex->GetHeight();

		frm.Duration = 1.f / (float)_FPS;

		frm.SliceSize.x = _vSlicePixelSize.x / m_AtlasTex->GetWidth();
		frm.SliceSize.y = _vSlicePixelSize.y / m_AtlasTex->GetHeight();

		m_vecFrm.push_back(frm);
	}
	
}

void CAnim2D::finaltick()
{
	if (m_Finish)
		return;

	m_Time += DT;

	if (m_vecFrm[m_CurIdx].Duration < m_Time)
	{		
		m_Time = m_Time - m_vecFrm[m_CurIdx].Duration;
		++m_CurIdx;

		if ((int)m_vecFrm.size() <= m_CurIdx)
		{
			m_CurIdx = m_vecFrm.size() - 1;
			m_Finish = true;
		}
	}	
}

void CAnim2D::Binding()
{
	// 아틀라스 텍스쳐 
	if (nullptr != m_AtlasTex)
		m_AtlasTex->Binding(14);

	// 프레임 정보
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIMATION);

	tAnim2DInfo info = {};
	info.vLeftTop = m_vecFrm[m_CurIdx].LeftTop;
	info.vSliceSize = m_vecFrm[m_CurIdx].SliceSize;
	info.UseAnim2D = 1;

	pCB->SetData(&info);
	pCB->Binding();
}
