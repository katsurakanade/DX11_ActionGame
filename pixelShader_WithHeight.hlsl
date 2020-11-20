#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
Texture2D g_TextureHeight : register(t2);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    
    float3 eyev = normalize(In.WorldPosition.xyz - CameraPosition.xyz);
   
    float height = g_TextureHeight.Sample(g_SamplerState, In.TexCoord).r;
    float2 tex = In.TexCoord + 0.05f * height * eyev.xy;
   
    float4 normalMap = g_TextureNormal.Sample(g_SamplerState, tex);
    normalMap = (normalMap * 2.0) - 1.0;
   
    float4 normal;
    normal.x = -normalMap.x;
    normal.y = normalMap.z;
    normal.z = -normalMap.y;
    normal.w = 0.0f;
    normal = normalize(normal);
   
    float light = -dot(normal.xyz, Light.Direction.xyz);
    light = saturate(light);
    
    outDiffuse = g_Texture.Sample(g_SamplerState, tex);
    outDiffuse.rgb *= light;
    outDiffuse.a *= 1.0f;
    
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10);
    outDiffuse.rgb += specular * 0.25;
}