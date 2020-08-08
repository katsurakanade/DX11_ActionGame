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

void main( in  float4 inPosition	: POSITION0, in  float4 inNormal	: NORMAL0, in  float2 inTexCoord: TEXCOORD0, in  float4 inDiffuse: COLOR0 , out float4 outDiffuse: SV_Target )
{
    float4 basecolor = g_BaseColor;
    float4 tex_color = g_Texture.Sample(g_SamplerState, inTexCoord);
	
	// îΩì]êFïœä∑
    //float4 inverted_color = 1 - tex_color;
    //inverted_color.a = tex_color.a;
    //inverted_color.rgb *= inverted_color.a;
	
    outDiffuse = tex_color /** inDiffuse*/ * basecolor;
}
