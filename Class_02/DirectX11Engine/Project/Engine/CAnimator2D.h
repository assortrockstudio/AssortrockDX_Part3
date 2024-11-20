#pragma once
#include "CComponent.h"

#include "CTexture.h"

class CAnim2D;

class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CAnim2D*>  m_mapAnim;
    CAnim2D*                m_CurAnim;
    bool                    m_Repeat;


public:
    void CreateAnimation(const wstring& _AnimName, Ptr<CTexture> _AltasTex, Vec2 _LeftTopPixelPos, Vec2 _vSlicePixelSize, int _FrameCount, UINT _FPS);
    CAnim2D* FindAnimation(const wstring& _AnimName);

public:
    virtual void finaltick() override;




public:
    CAnimator2D();
    ~CAnimator2D();
};

