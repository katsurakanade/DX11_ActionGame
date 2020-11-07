#include "Common.hlsl"

void main(in VS_IN_PARTICLE In, out PS_IN_PARTICLE Out)
{
    
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
   
    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);
    Out.TexCoord = In.TexCoord;

}

