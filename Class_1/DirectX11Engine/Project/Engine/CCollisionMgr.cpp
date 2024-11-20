#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CCollider2D.h"


CCollisionMgr::CCollisionMgr()
	: m_Matrix{}	
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::tick()
{
	for (UINT Row = 0; Row < MAX_LAYER; ++Row)
	{
		for (UINT Col = Row; Col < MAX_LAYER; ++Col)
		{			
			if (m_Matrix[Row] & (1 << Col))
			{
				CollisionBtwLayers(Row, Col);
			}
		}
	}
}

void CCollisionMgr::LayerCheck(UINT _LayerLeftIdx, UINT _LayerRightIdx)
{
	UINT Row = _LayerLeftIdx;
	UINT Col = _LayerRightIdx;

	if (Col < Row)
	{
		Row = _LayerRightIdx;
		Col = _LayerLeftIdx;
	}

	UINT CheckBit = (1 << Col);

	if (m_Matrix[Row] & CheckBit)
	{
		m_Matrix[Row] &= ~CheckBit;
	}
	else
	{
		m_Matrix[Row] |= CheckBit;
	}	
}



void CCollisionMgr::CollisionBtwLayers(UINT _Left, UINT _Right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	CLayer* pLeftLayer = pCurLevel->GetLayer(_Left);
	CLayer* pRightLayer = pCurLevel->GetLayer(_Right);

	const vector<CGameObject*>& vecLeft = pLeftLayer->GetObjects();
	const vector<CGameObject*>& vecRight = pRightLayer->GetObjects();

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->Collider2D())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->Collider2D())
				continue;

			CollisionBtwCollider2D(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D());
		}
	}
}

void CCollisionMgr::CollisionBtwCollider2D(CCollider2D* _LeftCol, CCollider2D* _RightCol)
{
	COL_ID id;
	id.LeftID = _LeftCol->GetID();
	id.RightID = _RightCol->GetID();

	map<LONGLONG, bool>::iterator iter = m_ColInfo.find(id.ID);
	if (iter == m_ColInfo.end())
	{
		m_ColInfo.insert(make_pair(id.ID, false));
		iter = m_ColInfo.find(id.ID);
	}

	// 현재 겹쳐있는 상태이다.
	if (IsCollision(_LeftCol, _RightCol))
	{		
		if (iter->second)
		{
			// Overlap
			_LeftCol->Overlap(_RightCol);
			_RightCol->Overlap(_LeftCol);
		}

		else
		{
			// BeginOverlap
			_LeftCol->BeginOverlap(_RightCol);
			_RightCol->BeginOverlap(_LeftCol);
		}

		iter->second = true;
	}

	// 충돌하고 있지 않다.
	else
	{
		if (iter->second)
		{
			// 이전에는 충돌중이었다.
			// EndOverlap
			_LeftCol->EndOverlap(_RightCol);
			_RightCol->EndOverlap(_LeftCol);
		}

		iter->second = false;
	}
}


bool CCollisionMgr::IsCollision(CCollider2D* _LeftCol, CCollider2D* _RightCol)
{
	// OBB
	// 0 -- 1
	// | \  |
	// 3 -- 2
	static Vec3 vLocal[4] =
	{
		Vec3(-0.5f, 0.5f, 0.f),
		Vec3(0.5f, 0.5f, 0.f),
		Vec3(0.5f, -0.5f, 0.f),
		Vec3(-0.5f, -0.5f, 0.f),
	};

	Vec3 vLeftCol[3] = {};
	Vec3 vRightCol[3] = {};

	for (int i = 0; i < 3; ++i)
	{
		vLeftCol[i] = XMVector3TransformCoord(vLocal[i], _LeftCol->GetWorldMat());
		vRightCol[i] = XMVector3TransformCoord(vLocal[i], _RightCol->GetWorldMat());
	}	

	Vec3 vLeftCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _LeftCol->GetWorldMat());
	Vec3 vRightCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _RightCol->GetWorldMat());
	Vec3 vCenter = vRightCenter - vLeftCenter;

	Vec3 arrProj[4] =
	{
		vLeftCol[1] - vLeftCol[0],
		vLeftCol[2] - vLeftCol[1],
		vRightCol[1] - vRightCol[0],
		vRightCol[2] - vRightCol[1],
	};

	
	// 각 투영 축으로 4번의 투영작업을 진행
	for (int i = 0; i < 4; ++i)
	{
		Vec3 vProj = arrProj[i];
		vProj.Normalize();

		float fProjLen = 0.f;
		for (int j = 0; j < 4; ++j)
		{
			fProjLen += fabs(arrProj[j].Dot(vProj));
		}

		// fProjLen : 투영벡터 4개를 투영축으로 투영한 길이의 합
		fProjLen *= 0.5f;
		float fCenter = fabs(vCenter.Dot(vProj));

		if (fProjLen < fCenter)
			return false;
	}

	return true;
}
