struct ParticleCompute
{
    float3 pos;
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

#define size_x    1024
#define size_y      1
#define size_z      1

// パーティクル
[numthreads(size_x, size_y, size_z)]
void CSFunc(const CSInput input)
{
    int index = input.dispatch.x;
    float t = Time[index].Time;
    float dt = Time[index].DeltaTime;
    
    float3 result;
    
    result = particle[index].pos + (particle[index].vel * dt);
        
    float4 col = float4(1, 1, 1, 1);
  
    BufOut[index].pos = result;
    BufOut[index].col = col;
    BufOut[index].life = particle[index].life - 1.0f;
    BufOut[index].vel = particle[index].vel;
  
}

