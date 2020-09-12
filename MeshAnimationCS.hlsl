
struct DEFORM_VERTEX
{
    float3 Position;
    float3 Normal;
    int mBoneNum;
    int mBoneName[4];
    float mBoneWeight[4];
};

struct COMPUTEMATRIX
{
	float4x4 cmatrix[4];
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

StructuredBuffer<DEFORM_VERTEX> deform : register(t0);
StructuredBuffer<COMPUTEMATRIX> computematrix : register(t1);
StructuredBuffer<VERTEX_3D> v3d : register(t2);

RWStructuredBuffer<VERTEX_3D> BufOut : register(u0);

#define size_x      1024
#define size_y      1
#define size_z      1

[numthreads(size_x, size_y, size_z)]
void CSFunc(const CSInput input)
{
    int index = input.dispatch.x;
    
    DEFORM_VERTEX def = deform[index];
    COMPUTEMATRIX cm = computematrix[index];
     
    
   
    float4x4 cmatrix[4];
    
    cmatrix[0] = cm.cmatrix[0];
    cmatrix[1] = cm.cmatrix[1];
    cmatrix[2] = cm.cmatrix[2];
    cmatrix[3] = cm.cmatrix[3];
    
    float4x4 outMatrix;
    
    outMatrix._11 = cmatrix[0]._11 * def.mBoneWeight[0] + cmatrix[1]._11 * def.mBoneWeight[1] + cmatrix[2]._11 * def.mBoneWeight[2] + cmatrix[3]._11 * def.mBoneWeight[3];
    outMatrix._12 = cmatrix[0]._12 * def.mBoneWeight[0] + cmatrix[1]._12 * def.mBoneWeight[1] + cmatrix[2]._12 * def.mBoneWeight[2] + cmatrix[3]._12 * def.mBoneWeight[3];
    outMatrix._13 = cmatrix[0]._13 * def.mBoneWeight[0] + cmatrix[1]._13 * def.mBoneWeight[1] + cmatrix[2]._13 * def.mBoneWeight[2] + cmatrix[3]._13 * def.mBoneWeight[3];
    outMatrix._14 = cmatrix[0]._14 * def.mBoneWeight[0] + cmatrix[1]._14 * def.mBoneWeight[1] + cmatrix[2]._14 * def.mBoneWeight[2] + cmatrix[3]._14 * def.mBoneWeight[3];

    outMatrix._21 = cmatrix[0]._21 * def.mBoneWeight[0] + cmatrix[1]._21 * def.mBoneWeight[1] + cmatrix[2]._21 * def.mBoneWeight[2] + cmatrix[3]._21 * def.mBoneWeight[3];
    outMatrix._22 = cmatrix[0]._22 * def.mBoneWeight[0] + cmatrix[1]._22 * def.mBoneWeight[1] + cmatrix[2]._22 * def.mBoneWeight[2] + cmatrix[3]._22 * def.mBoneWeight[3];
    outMatrix._23 = cmatrix[0]._23 * def.mBoneWeight[0] + cmatrix[1]._23 * def.mBoneWeight[1] + cmatrix[2]._23 * def.mBoneWeight[2] + cmatrix[3]._23 * def.mBoneWeight[3];
    outMatrix._24 = cmatrix[0]._24 * def.mBoneWeight[0] + cmatrix[1]._24 * def.mBoneWeight[1] + cmatrix[2]._24 * def.mBoneWeight[2] + cmatrix[3]._24 * def.mBoneWeight[3];
    
    outMatrix._31 = cmatrix[0]._31 * def.mBoneWeight[0] + cmatrix[1]._31 * def.mBoneWeight[1] + cmatrix[2]._31 * def.mBoneWeight[2] + cmatrix[3]._31 * def.mBoneWeight[3];
    outMatrix._32 = cmatrix[0]._32 * def.mBoneWeight[0] + cmatrix[1]._32 * def.mBoneWeight[1] + cmatrix[2]._32 * def.mBoneWeight[2] + cmatrix[3]._32 * def.mBoneWeight[3];
    outMatrix._33 = cmatrix[0]._33 * def.mBoneWeight[0] + cmatrix[1]._33 * def.mBoneWeight[1] + cmatrix[2]._33 * def.mBoneWeight[2] + cmatrix[3]._33 * def.mBoneWeight[3];
    outMatrix._34 = cmatrix[0]._34 * def.mBoneWeight[0] + cmatrix[1]._34 * def.mBoneWeight[1] + cmatrix[2]._34 * def.mBoneWeight[2] + cmatrix[3]._34 * def.mBoneWeight[3];
    
    outMatrix._41 = cmatrix[0]._41 * def.mBoneWeight[0] + cmatrix[1]._41 * def.mBoneWeight[1] + cmatrix[2]._41 * def.mBoneWeight[2] + cmatrix[3]._41 * def.mBoneWeight[3];
    outMatrix._42 = cmatrix[0]._42 * def.mBoneWeight[0] + cmatrix[1]._42 * def.mBoneWeight[1] + cmatrix[2]._42 * def.mBoneWeight[2] + cmatrix[3]._42 * def.mBoneWeight[3];
    outMatrix._43 = cmatrix[0]._43 * def.mBoneWeight[0] + cmatrix[1]._43 * def.mBoneWeight[1] + cmatrix[2]._43 * def.mBoneWeight[2] + cmatrix[3]._43 * def.mBoneWeight[3];
    outMatrix._44 = cmatrix[0]._44 * def.mBoneWeight[0] + cmatrix[1]._44 * def.mBoneWeight[1] + cmatrix[2]._44 * def.mBoneWeight[2] + cmatrix[3]._44 * def.mBoneWeight[3];
    
    def.Position = v3d[index].Position;
    
    float3 pos = mul(def.Position, outMatrix).xyz;

    outMatrix._14 = 0.0f;
    outMatrix._24 = 0.0f;
    outMatrix._34 = 0.0f;

    def.Normal.x = v3d[index].Normal.x;
    def.Normal.y = v3d[index].Normal.y;
    def.Normal.z = v3d[index].Normal.z;
    
    float3 nor = mul(def.Normal, outMatrix).xyz;
    
    BufOut[index].Position.x = pos.x;
    BufOut[index].Position.y = pos.y;
    BufOut[index].Position.z = pos.z;

    BufOut[index].Normal.x = nor.x;
    BufOut[index].Normal.y = nor.y;
    BufOut[index].Normal.z = nor.z;
   
    BufOut[index].TexCoord.x = v3d[index].TexCoord.x;
    BufOut[index].TexCoord.y = v3d[index].TexCoord.y;    


}

