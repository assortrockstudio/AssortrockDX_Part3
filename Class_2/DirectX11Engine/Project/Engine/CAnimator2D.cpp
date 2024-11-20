#include "pch.h"
#include "CAnimator2D.h"

#include "CAnim2D.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
	, m_CurAnim(nullptr)
	, m_Repeat(false)
{

}

CAnimator2D::~CAnimator2D()
{

}

void CAnimator2D::finaltick()
{
	if (nullptr == m_CurAnim)
		return;

	m_CurAnim->finaltick();
}


void CAnimator2D::CreateAnimation(const wstring& _AnimName, Ptr<CTexture> _AltasTex
							, Vec2 _LeftTopPixelPos, Vec2 _vSlicePixelSize, int _FrameCount, UINT _FPS)
{
	assert(!FindAnimation(_AnimName));

	CAnim2D* pAnim = new CAnim2D;
	pAnim->SetName(_AnimName);
	pAnim->Create(_AltasTex, _LeftTopPixelPos, _vSlicePixelSize, _FrameCount, _FPS);

	pAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(_AnimName, pAnim));
}

CAnim2D* CAnimator2D::FindAnimation(const wstring& _AnimName)
{
	map<wstring, CAnim2D*>::iterator iter = m_mapAnim.find(_AnimName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}
