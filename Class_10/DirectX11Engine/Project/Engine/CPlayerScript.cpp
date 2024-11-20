#include "pch.h"
#include "CPlayerScript.h"

#include "CMissileScript.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider2D.h"
#include "CStructuredBuffer.h"


CPlayerScript::CPlayerScript()
	: m_Speed(500.f)
	, m_TestBuffer(nullptr)
{
	m_TestBuffer = new CStructuredBuffer;
}

CPlayerScript::~CPlayerScript()
{
	if (nullptr != m_TestBuffer)
		delete m_TestBuffer;
}

void CPlayerScript::begin()
{
	Vec4 vData = Vec4(1.f, 2.f, 3.f, 4.f);
	m_TestBuffer->Create(sizeof(Vec4), 1, &vData);
	m_TestBuffer->Binding(20);
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
		if (Collider2D()->IsActive())
		{
			Collider2D()->Deactivate();
			m_Speed = 10.f;
		}
		else
		{
			Collider2D()->Activate();
		}

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

		SpawnObject(0, pNewObj);
	}


	if (IsValid(m_TargetMon))
	{
		Vec3 vDir = m_TargetMon->Transform()->GetWorldPos() - Transform()->GetWorldPos();
		vDir.Normalize();

		vCurPos += vDir * m_Speed * DT;
	}

	Transform()->SetRelativePos(vCurPos);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{	
	
}

void CPlayerScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	int a = 0;
}
