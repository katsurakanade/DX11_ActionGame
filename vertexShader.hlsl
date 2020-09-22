#include "Common.hlsl"

cbuffer WorldBuffer : register(b0)
{
    matrix World;
}
cbuffer ViewBuffer : register(b1)
{
    matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}
cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}

void main(in VS_IN In, out PS_IN Out)
{
    
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    Out.Position = mul(In.Position, wvp);
    Out.Normal = In.Normal;
    Out.TexCoord = In.TexCoord;
	
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0);
	
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
	
    if (Light.Enable)
    {	
        Out.Diffuse = In.Diffuse * Material.Diffuse * Light.Diffuse;
        Out.Diffuse += In.Diffuse * Material.Ambient * Light.Ambient;
        Out.Diffuse += Material.Emission;
    }
    
    else
    {
        Out.Diffuse = In.Diffuse * Material.Diffuse;
    }

    Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;

}

