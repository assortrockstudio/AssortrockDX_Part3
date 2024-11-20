#ifndef _STD2D
#define _STD2D

#include "value.fx"

StructuredBuffer<float4> g_TestBuffer : register(t20);


struct VS_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    
    float3 vWorldPos : POSITION;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    // ����� ���Ҷ� 3���� ��ǥ�� 4�������� Ȯ��(������ǥ)    
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
    
    output.vWorldPos = vWorldPos;
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    
    if (g_TestBuffer[0].w == 4.f)
        return float4(1.f, 0.f, 0.f, 1.f);
    
    if (UseAnim2D)
    {
        float2 vBkgroundLT = vLeftTop - (vBackground - vSliceSize) * 0.5f;
        float2 vUV = (vBkgroundLT + _in.vUV * vBackground) - vOffset;
        
        if (vUV.x < vLeftTop.x || vLeftTop.x + vSliceSize.x < vUV.x
            || vUV.y < vLeftTop.y || vLeftTop.y + vSliceSize.y < vUV.y)
        {
            //vColor = float4(1.f, 1.f, 0.f, 1.f);
            discard;
        }
        else
        {
            vColor = g_Atlas.Sample(g_sam_0, vUV);
        }
    }
    else
    {
        vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
        
    
    // ���� ó��
    float3 vLightPow = (float3) 0.f;
        
    // Directional Light
    if (0 == g_Light2D[0].LightType)
    {
        vLightPow = g_Light2D[0].Light.vDiffuse.rgb + g_Light2D[0].Light.vAmbient.rgb;
    }
    
    // PointLight
    else if (1 == g_Light2D[0].LightType)
    {
        // �ȼ��� ���彺���̽�
        float fDist = distance(g_Light2D[0].WorldPos.xy, _in.vWorldPos.xy);
        if (fDist < g_Light2D[0].Range)
        {
            vLightPow = g_Light2D[0].Light.vDiffuse;
        }        
    }
    
    // SpotLight
    else
    {
        
    }
        
    vColor.rgb *= vLightPow;
    
    return vColor;
}

#endif