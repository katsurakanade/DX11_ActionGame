
#include "Common.hlsl"

// マトリクスバッファ
cbuffer WorldBuffer : register( b0 )
{
	matrix World;
}
cbuffer ViewBuffer : register( b1 )
{
	matrix View;
}
cbuffer ProjectionBuffer : register( b2 )
{
	matrix Projection;
}

// マテリアルバッファ
struct MATERIAL
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float			Shininess;
	float3		Dummy;//16bit境界用
};

cbuffer MaterialBuffer : register( b3 )
{
	MATERIAL	Material;
}

// ライトバッファ
struct LIGHT
{
	bool		Enable;
	bool3		Dummy;//16bit境界用
	float4		Direction;
	float4		Diffuse;
	float4		Ambient;
};

cbuffer LightBuffer : register( b4 )
{
	LIGHT		Light;
}


void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

    Out.Position = mul( In.Position, wvp);
    Out.Normal = In.Normal;
    Out.TexCoord = In.TexCoord;
	
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	
	if (Light.Enable)
	{
				
        float light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz);

        Out.Diffuse = In.Diffuse * Material.Diffuse * light * Light.Diffuse;
        Out.Diffuse += In.Diffuse * Material.Ambient * Light.Ambient;
        Out.Diffuse += Material.Emission;
    }
	else
	{
        Out.Diffuse = In.Diffuse * Material.Diffuse;
    }

    Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;

}

