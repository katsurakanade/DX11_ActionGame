#include "Common.hlsl"

StructuredBuffer<float3> Position : register(t2);

void main(in VS_IN_PARTICLE In, out PS_IN_PARTICLE Out)
{
       
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
   
    In.Position.xyz += Position[In.InstanceID];
  
    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);
    Out.TexCoord = In.TexCoord;

}


