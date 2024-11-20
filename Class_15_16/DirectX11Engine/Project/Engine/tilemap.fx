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
    
    vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);    
    
    return vOutColor;
}

#endif