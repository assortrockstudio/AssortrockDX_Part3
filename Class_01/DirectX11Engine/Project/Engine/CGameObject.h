#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CScript;


#define GET_COMPONENT(Type, TYPE) class C##Type* Type() { return ( C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::TYPE]; }

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*       m_RenderCom;
    vector<CScript*>        m_vecScripts;

    CGameObject*            m_Parent;
    vector<CGameObject*>    m_vecChild;

    int                     m_LayerIdx; // GameObject �� �ҼӵǾ��ִ� Layer

public:
    void begin();       // ������ ���۵� ��, ������ �շ��� ��
    void tick();        // �� �����Ӹ��� ȣ��, DT ���� �� ���� ����
    void finaltick();   // tick ���� �߻��� �ϵ��� ������ �۾� or ���ҽ� ���ε� �� ���� ������ ����
    void render();      // ȭ�鿡 �׷����� �Լ�

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);


    void AddChild(CGameObject* _Object);
    const vector<CGameObject*>& GetChildren() { return m_vecChild; }
    CGameObject* GetParent() { return m_Parent; }

    const vector<CScript*>& GetScripts() { return m_vecScripts; }

private:
    void SetLayerIdx(int _Idx) { m_LayerIdx = _Idx; }


public:
    CGameObject();
    ~CGameObject();


    friend class CLayer;
};

