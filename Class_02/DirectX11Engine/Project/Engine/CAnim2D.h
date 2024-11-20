#pragma once
#include "CEntity.h"

struct tAnim2DFrm
{
    Vec2    LeftTop;
    Vec2    SliceSize;
    float   Duration;
};

class CTexture;
class CAnimator2D;

class CAnim2D :
    public CEntity
{
private:
    CAnimator2D*        m_Animator;
    vector<tAnim2DFrm>  m_vecFrm;
    int                 m_CurIdx;
    bool                m_Finish;

    Ptr<CTexture>       m_AtlasTex;

    
public:
    void Create(Ptr<CTexture> _AltasTex, Vec2 _LeftTopPixelPos, Vec2 _vSlicePixelSize, int _FrameCount, UINT _FPS);



public:
    void finaltick();



public:
    CAnim2D();
    ~CAnim2D();

    friend class CAnimator2D;
};

