

struct VS_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy; //16bit‹«ŠE—p
};


struct LIGHT
{
    bool Enable;
    bool3 Dummy; //16bit‹«ŠE—p
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};


cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}
