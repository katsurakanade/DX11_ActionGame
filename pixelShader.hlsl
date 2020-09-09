
#include "Common.hlsl"

cbuffer MaterialBuffer : register( b1 )
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		    Shininess;
	float3		Dummy;
}

float4 g_BaseColor : register(t1);
Texture2D	g_Texture : register(t0);

SamplerState	g_SamplerState : register( s0 );

void main(in PS_IN In , out float4 outDiffuse : SV_Target)
{
    float4 basecolor = g_BaseColor;
    float4 tex_color = g_Texture.Sample(g_SamplerState, In.TexCoord);
		
    outDiffuse = tex_color * In.Diffuse * basecolor;
}
