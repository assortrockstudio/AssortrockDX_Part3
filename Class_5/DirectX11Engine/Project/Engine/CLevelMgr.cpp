#include "pch.h"
#include "CLevelMgr.h"

#include "CAssetMgr.h"

#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "components.h"

#include "CPlayerScript.h"
#include "CCameraMoveScript.h"

#include "CCollisionMgr.h"


CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
	{
		delete m_CurLevel;
	}	
}

void CLevelMgr::init()
{
	m_CurLevel = new CLevel;

	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Player");
	m_CurLevel->GetLayer(2)->SetName(L"Monster");


	// Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->SetCameraPriority(0); // 메인 카메라로 설정
	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	
	m_CurLevel->AddObject(0, pCamObj);


	// Player 오브젝트 생성
	CGameObject* pPlayer = new CGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new CTransform);
	pPlayer->AddComponent(new CMeshRender);
	pPlayer->AddComponent(new CCollider2D);
	pPlayer->AddComponent(new CAnimator2D);
	pPlayer->AddComponent(new CPlayerScript);
		
	pPlayer->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pPlayer->Transform()->SetRelativeScale(200.f, 200.f, 0.5f);

	pPlayer->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pPlayer->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\Character.png"));

	pPlayer->Collider2D()->SetAbsolute(false);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	Ptr<CTexture> pAltas = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\link.png", L"texture\\link.png");
	pPlayer->Animator2D()->CreateAnimation(L"MOVE_DOWN", pAltas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(240.f, 260.f), 10, 16);
	pPlayer->Animator2D()->CreateAnimation(L"IDLE_RIGHT", pAltas, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(240.f, 260.f), 3, 2);

	pPlayer->Animator2D()->Play(L"IDLE_RIGHT", true);

	m_CurLevel->AddObject(1, pPlayer, false);


	// Monster 오브젝트 생성
	CGameObject* pMonster = new CGameObject;
	pMonster->SetName(L"Monster");
	pMonster->AddComponent(new CTransform);
	pMonster->AddComponent(new CMeshRender);
	pMonster->AddComponent(new CCollider2D);

	pMonster->Transform()->SetRelativePos(Vec3(600.f, 0.f, 0.f));
	pMonster->Transform()->SetRelativeScale(200.f, 200.f, 0.f);
	pMonster->Transform()->SetAbsolute(true);

	pMonster->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pMonster->Collider2D()->SetAbsolute(false);
	pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pMonster->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	
	m_CurLevel->AddObject(1, pMonster, false);

	// Level 의 충돌설정
	CCollisionMgr::GetInst()->LayerCheck(1, 1);
	CCollisionMgr::GetInst()->LayerCheck(2, 1);	
}

void CLevelMgr::tick()
{
	if(nullptr != m_CurLevel)	
	{
		m_CurLevel->tick();
		m_CurLevel->finaltick();
	}
}