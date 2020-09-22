#include "Common.hlsl"

cbuffer CameraBuffer : register(b5)
{
    float4 CameraPosition;
}

Texture2D	g_Texture : register(t0);
float4 g_BaseColor : register(t1);
SamplerState	g_SamplerState : register(s0);

void main(in PS_IN In , out float4 outDiffuse : SV_Target)
{

    float4 normal = normalize(In.Normal);
    
    float4 basecolor = g_BaseColor;
    float4 tex_color = g_Texture.Sample(g_SamplerState, In.TexCoord);
	    
    float light = -dot(normal.xyz, Light.Direction.xyz);
    light = saturate(light);
    
    outDiffuse = tex_color * In.Diffuse * basecolor;
    outDiffuse.a *= In.Diffuse.a;
    
    float3 eyev = In.Position.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 30);
    outDiffuse.rgb += specular;
        
    float rim = 1.0f + dot(eyev, normal.xyz);
    rim = pow(rim, 2) * 0.05f;
    outDiffuse.rgb += rim;
}
