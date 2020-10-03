struct ParticleCompute
{
    float3 vertex[4];
    float3 vel;
    float4 col;
    float life;
};

struct TimeCompute
{
    float Time;
    float DeltaTime;
};

struct CSInput
{
    uint3 groupThread : SV_GroupThreadID;
    uint3 group : SV_GroupID;
    uint groupIndex : SV_GroupIndex;
    uint3 dispatch : SV_DispatchThreadID;
};

StructuredBuffer<ParticleCompute> particle : register(t0);
StructuredBuffer<TimeCompute> Time : register(t1);
RWStructuredBuffer<ParticleCompute> BufOut : register(u0);

#define size_x      1024
#define size_y      1
#define size_z      1

// パーティクル
[numthreads(size_x, size_y, size_z)]
void CSFunc(const CSInput input)
{
    int index = input.dispatch.x;
    float t = Time[index].Time;
    float dt = Time[index].DeltaTime;
    
    float alife = particle[index].life - 1.0f;
    
    float3 result[4];
    
    result[0] = particle[index].vertex[0] + (particle[index].vel * dt) * 50;
    result[1] = particle[index].vertex[1] + (particle[index].vel * dt) * 50;
    result[2] = particle[index].vertex[2] + (particle[index].vel * dt) * 50;
    result[3] = particle[index].vertex[3] + (particle[index].vel * dt) * 50;
        
    float4 col;
    col = float4(1, 1, 1, 1);
    
    BufOut[index].vertex[0] = result[0];
    BufOut[index].vertex[1] = result[1];
    BufOut[index].vertex[2] = result[2];
    BufOut[index].vertex[3] = result[3];
    BufOut[index].col = col;
    BufOut[index].life = particle[index].life;

  
}

