//struct DEFORM_VERTEX
//{
//    float3 Position;
//    float3 Normal;
//    int mBoneNum;
//    int mBoneName[4];
//    float mBoneWeight[4];
//};

struct COMPUTEMATRIX
{
    float4x4 outMatrix;
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

//StructuredBuffer<DEFORM_VERTEX> deform : register(t0);
StructuredBuffer<COMPUTEMATRIX> computematrix : register(t0);
StructuredBuffer<VERTEX_3D> v3d : register(t1);

RWStructuredBuffer<VERTEX_3D> BufOut : register(u0);

#define size_x      128
#define size_y      1
#define size_z      1

[numthreads(size_x, size_y, size_z)]
void CSFunc(const CSInput input)
{
    
    COMPUTEMATRIX cm = computematrix[input.dispatch.x];
    
     //DEFORM_VERTEX def = deform[input.dispatch.x];
    
    //float4x4 outMatrix;
   
    //outMatrix._11 = cm.cmatrix[0]._11 * def.mBoneWeight[0] + cm.cmatrix[1]._11 * def.mBoneWeight[1] + cm.cmatrix[2]._11 * def.mBoneWeight[2] + cm.cmatrix[3]._11 * def.mBoneWeight[3];
    //outMatrix._12 = cm.cmatrix[0]._12 * def.mBoneWeight[0] + cm.cmatrix[1]._12 * def.mBoneWeight[1] + cm.cmatrix[2]._12 * def.mBoneWeight[2] + cm.cmatrix[3]._12 * def.mBoneWeight[3];
    //outMatrix._13 = cm.cmatrix[0]._13 * def.mBoneWeight[0] + cm.cmatrix[1]._13 * def.mBoneWeight[1] + cm.cmatrix[2]._13 * def.mBoneWeight[2] + cm.cmatrix[3]._13 * def.mBoneWeight[3];
    //outMatrix._14 = cm.cmatrix[0]._14 * def.mBoneWeight[0] + cm.cmatrix[1]._14 * def.mBoneWeight[1] + cm.cmatrix[2]._14 * def.mBoneWeight[2] + cm.cmatrix[3]._14 * def.mBoneWeight[3];

    //outMatrix._21 = cm.cmatrix[0]._21 * def.mBoneWeight[0] + cm.cmatrix[1]._21 * def.mBoneWeight[1] + cm.cmatrix[2]._21 * def.mBoneWeight[2] + cm.cmatrix[3]._21 * def.mBoneWeight[3];
    //outMatrix._22 = cm.cmatrix[0]._22 * def.mBoneWeight[0] + cm.cmatrix[1]._22 * def.mBoneWeight[1] + cm.cmatrix[2]._22 * def.mBoneWeight[2] + cm.cmatrix[3]._22 * def.mBoneWeight[3];
    //outMatrix._23 = cm.cmatrix[0]._23 * def.mBoneWeight[0] + cm.cmatrix[1]._23 * def.mBoneWeight[1] + cm.cmatrix[2]._23 * def.mBoneWeight[2] + cm.cmatrix[3]._23 * def.mBoneWeight[3];
    //outMatrix._24 = cm.cmatrix[0]._24 * def.mBoneWeight[0] + cm.cmatrix[1]._24 * def.mBoneWeight[1] + cm.cmatrix[2]._24 * def.mBoneWeight[2] + cm.cmatrix[3]._24 * def.mBoneWeight[3];
    
    //outMatrix._31 = cm.cmatrix[0]._31 * def.mBoneWeight[0] + cm.cmatrix[1]._31 * def.mBoneWeight[1] + cm.cmatrix[2]._31 * def.mBoneWeight[2] + cm.cmatrix[3]._31 * def.mBoneWeight[3];
    //outMatrix._32 = cm.cmatrix[0]._32 * def.mBoneWeight[0] + cm.cmatrix[1]._32 * def.mBoneWeight[1] + cm.cmatrix[2]._32 * def.mBoneWeight[2] + cm.cmatrix[3]._32 * def.mBoneWeight[3];
    //outMatrix._33 = cm.cmatrix[0]._33 * def.mBoneWeight[0] + cm.cmatrix[1]._33 * def.mBoneWeight[1] + cm.cmatrix[2]._33 * def.mBoneWeight[2] + cm.cmatrix[3]._33 * def.mBoneWeight[3];
    //outMatrix._34 = cm.cmatrix[0]._34 * def.mBoneWeight[0] + cm.cmatrix[1]._34 * def.mBoneWeight[1] + cm.cmatrix[2]._34 * def.mBoneWeight[2] + cm.cmatrix[3]._34 * def.mBoneWeight[3];
    
    //outMatrix._41 = cm.cmatrix[0]._41 * def.mBoneWeight[0] + cm.cmatrix[1]._41 * def.mBoneWeight[1] + cm.cmatrix[2]._41 * def.mBoneWeight[2] + cm.cmatrix[3]._41 * def.mBoneWeight[3];
    //outMatrix._42 = cm.cmatrix[0]._42 * def.mBoneWeight[0] + cm.cmatrix[1]._42 * def.mBoneWeight[1] + cm.cmatrix[2]._42 * def.mBoneWeight[2] + cm.cmatrix[3]._42 * def.mBoneWeight[3];
    //outMatrix._43 = cm.cmatrix[0]._43 * def.mBoneWeight[0] + cm.cmatrix[1]._43 * def.mBoneWeight[1] + cm.cmatrix[2]._43 * def.mBoneWeight[2] + cm.cmatrix[3]._43 * def.mBoneWeight[3];
    //outMatrix._44 = cm.cmatrix[0]._44 * def.mBoneWeight[0] + cm.cmatrix[1]._44 * def.mBoneWeight[1] + cm.cmatrix[2]._44 * def.mBoneWeight[2] + cm.cmatrix[3]._44 * def.mBoneWeight[3];
    
    float4 pos = mul(float4(v3d[input.dispatch.x].Position, 1.0f), cm.outMatrix);
   
    cm.outMatrix._14 = 0.0f;
    cm.outMatrix._24 = 0.0f;
    cm.outMatrix._34 = 0.0f;

    float3 nor = mul(float4(v3d[input.dispatch.x].Normal, 1.0f), cm.outMatrix);
    
    BufOut[input.dispatch.x].Position = pos;
    BufOut[input.dispatch.x].Normal = nor;
    BufOut[input.dispatch.x].TexCoord.x = v3d[input.dispatch.x].TexCoord.x;
    BufOut[input.dispatch.x].TexCoord.y = v3d[input.dispatch.x].TexCoord.y;
}

