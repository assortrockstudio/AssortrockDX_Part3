#include "pch.h"
#include "CAnim2D.h"

#include "CTexture.h"

CAnim2D::CAnim2D()
	: m_CurIdx(0)
	, m_Finish(false)
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
	m_CurIdx = 0;
}