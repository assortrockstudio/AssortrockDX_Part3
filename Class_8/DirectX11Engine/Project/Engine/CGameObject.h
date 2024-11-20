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

    int                     m_LayerIdx; // GameObject 가 소속되어있는 Layer
    bool                    m_Dead; // 오브젝트 Life 체크


public:
    void begin();       // 레벨이 시작될 때, 레벨에 합류할 때
    void tick();        // 매 프레임마다 호출, DT 동안 할 일을 구현
    void finaltick();   // tick 에서 발생한 일들의 마무리 작업 or 리소스 바인딩 및 관련 데이터 연산
    void render();      // 화면에 그려지는 함수

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(Animator2D, ANIMATOR2D);


    void AddChild(CGameObject* _Object);
    const vector<CGameObject*>& GetChildren() { return m_vecChild; }
    CGameObject* GetParent() { return m_Parent; }
    const vector<CScript*>& GetScripts() { return m_vecScripts; }

    template<typename T>
    T* GetScript();

    bool IsDead() { return m_Dead; }
    void Destroy();

private:
    void SetLayerIdx(int _Idx) { m_LayerIdx = _Idx; }


public:
    CGameObject();
    ~CGameObject();


    friend class CLayer;
    friend class CTaskMgr;
};

template<typename T>
inline T* CGameObject::GetScript()
{
    for (size_t i = 0; i < m_vecScripts.size(); ++i)
    {
        if (dynamic_cast<T*>(m_vecScripts[i]))
            return (T*)m_vecScripts[i];
    }

    return nullptr;
}
