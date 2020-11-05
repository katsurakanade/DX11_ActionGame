#include "Common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_Texture_Normal : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 normal;
    
    float4 normalMap = g_Texture_Normal.Sample(g_SamplerState, In.TexCoord);
    normalMap = (normalMap * 2.0) - 1.0;
   
    normal.x = -normalMap.x;
    normal.y = normalMap.z;
    normal.z = normalMap.y;
    normal.w = 0.0;

    float light = -dot(normal.xyz, Light.Direction.xyz);
    light = saturate(light);
    
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse += Material.Ambient * Light.Ambient;
    outDiffuse *= Material.Diffuse;
    
    outDiffuse.rgb *= In.Diffuse.rgb * light;
    outDiffuse.a *= In.Diffuse.a * Material.Diffuse.a;
    
    //Specular
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, Material.Shininess);
    outDiffuse.rgb += specular * Material.Specular.xyz;
    
    float rim = 1.0f + dot(eyev, normal.xyz);
    rim = pow(rim, 2) * 0.1f;
    outDiffuse.rgb += rim;
    
 
}