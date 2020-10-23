struct COMPUTEMATRIX
{
    float4x4 cmatrix[4];
    float mBoneWeight[4];
};

struct VERTEX_3D
{
    float3 Position;
    float3 Normal;
    float4 Diffuse;
    float2 TexCoord;
};

struct CSInput
{
    uint3 groupThread : SV_GroupThreadID;
    uint3 group : SV_GroupID;
    uint groupIndex : SV_GroupIndex;
    uint3 dispatch : SV_DispatchThreadID;
};

StructuredBuffer<COMPUTEMATRIX> computematrix : register(t0);
StructuredBuffer<VERTEX_3D> v3d : register(t1);
RWStructuredBuffer<VERTEX_3D> BufOut : register(u0);

#define size_x      1024
#define size_y      1
#define size_z      1

// GPU スキンメッシュアニメーション
[numthreads(size_x, size_y, size_z)]
void CSFunc(const CSInput input)
{
    
    COMPUTEMATRIX cm = computematrix[input.dispatch.x];
   
    float4x4 outMatrix;
   
    outMatrix = cm.cmatrix[0] * cm.mBoneWeight[0] + cm.cmatrix[1] * cm.mBoneWeight[1] + cm.cmatrix[2] * cm.mBoneWeight[2] + cm.cmatrix[3] * cm.mBoneWeight[3];
    
    float4 pos = mul(float4(v3d[input.dispatch.x].Position, 1.0f), outMatrix);
   
    outMatrix._14 = 0.0f;
    outMatrix._24 = 0.0f;
    outMatrix._34 = 0.0f;

    float4 nor = mul(float4(v3d[input.dispatch.x].Normal, 0.0f), outMatrix);
    
    BufOut[input.dispatch.x].Position = pos.xyz;
    BufOut[input.dispatch.x].Normal = nor.xyz;
    BufOut[input.dispatch.x].TexCoord.x = v3d[input.dispatch.x].TexCoord.x;
    BufOut[input.dispatch.x].TexCoord.y = v3d[input.dispatch.x].TexCoord.y;
}

