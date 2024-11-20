#include "pch.h"
#include "CPlayerScript.h"

#include "CMissileScript.h"
#include "CLevelMgr.h"
#include "CLevel.h"


CPlayerScript::CPlayerScript()
	: m_Speed(100.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::tick()
{
	// 키 입력에 따른 위치이동
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::UP))
	{
		vCurPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		vCurPos.y -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		vCurPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vCurPos.x += DT * m_Speed;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CGameObject* pNewObj = new CGameObject;
		pNewObj->AddComponent(new CTransform);
		pNewObj->AddComponent(new CMeshRender);
		pNewObj->AddComponent(new CMissileScript);

		Vec3 vPos = Transform()->GetRelativePos();
		vPos.y += (Transform()->GetRelativeScale().y / 2.f);
		pNewObj->Transform()->SetRelativePos(vPos);
		pNewObj->Transform()->SetRelativeScale(Vec3(40.f, 40.f, 40.f));

		pNewObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pNewObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(0, pNewObj);
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}
