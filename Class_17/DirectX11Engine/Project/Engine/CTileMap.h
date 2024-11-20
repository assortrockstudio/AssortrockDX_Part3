#pragma once
#include "CRenderComponent.h"

class CTileMap :
    public CRenderComponent
{
private:
    UINT            m_Row;          // Tile Row Size
    UINT            m_Col;          // Tile Colum Size
    Vec2            m_TileEachSize; // �� Ÿ�� 1���� ũ��

    Ptr<CTexture>   m_Atlas;
    UINT            m_AtlasMaxRow;
    UINT            m_AtlasMaxCol;
    Vec2            m_AtlasTileEachSize;
    Vec2            m_AtlasResolution;

public:
    void SetRowCol(UINT _Row, UINT _Col);
    void SetAltasTexture(Ptr<CTexture> _Tex);
    void SetAltasTileSize(Vec2 _TileSize);
    void SetTileEachSize(Vec2 _vSize);

public:
    virtual void finaltick() override;
    virtual void render() override;

public:
    CTileMap();
    ~CTileMap();
};

