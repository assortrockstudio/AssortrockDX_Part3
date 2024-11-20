#ifndef _TILEMAP
#define _TILEMAP

#include "value.fx"

struct VS_IN
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

// ============================
// TileMapShader
// Parameter
#define AtlasMaxRow         g_int_0
#define AtlasMaxCol         g_int_1
#define TileImgIdx          g_int_2
#define AtlasResolution     g_vec2_0
#define AtlasTileSize       g_vec2_1
#define TileColRow          g_vec2_2
// ============================

VS_OUT VS_TileMap(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;    
    
    return output;
}


float4 PS_TileMap(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    _in.vUV *= TileColRow;
    _in.vUV = _in.vUV - floor(_in.vUV);    
    
    float2 TileSize = AtlasTileSize / AtlasResolution;    
    float2 vUV = TileSize * _in.vUV;
    
    int row = TileImgIdx / AtlasMaxCol;
    int col = TileImgIdx % AtlasMaxCol;
    
    vUV += float2(col * TileSize.x, row * TileSize.y);
    
    vOutColor = g_tex_0.Sample(g_sam_0, vUV);
    
    return vOutColor;
}

#endif