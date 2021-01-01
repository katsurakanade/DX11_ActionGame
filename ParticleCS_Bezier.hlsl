struct ParticleCompute
{
    float3 pos;
    float3 vel;
    float4 col;
    float life;
};

struct BezierCompute
{
    float3 p0;
    float3 p1;
    float3 p2;
    float t;
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
StructuredBuffer<BezierCompute> Bezier : register(t2);
RWStructuredBuffer<ParticleCompute> BufOut : register(u0);

#define size_x    1024
#define size_y      1
#define size_z      1

float3 BezierC(float3 p0, float3 p1, float3 p2, float t)
{
    float3 p0p1 = (1 - t) * p0 + t * p1;
    float3 p1p2 = (1 - t) * p1 + t * p2;
    float3 result = (1 - t) * p0p1 + t * p1p2;
    return result;
}

// パーティクル
[numthreads(size_x, size_y, size_z)]
void CSFunc(const CSInput input)
{
    int index = input.dispatch.x;
    float t = Time[index].Time;
    float dt = Time[index].DeltaTime;
    
    float3 result;

    result = BezierC(Bezier[index].p0, Bezier[index].p1, Bezier[index].p2, Bezier[index].t);
        
    float4 col = float4(1, 1, 1, 1);
  
    BufOut[index].pos = result;
    BufOut[index].col = col;
    
    if (Bezier[index].t > 0)
    {
        BufOut[index].life = particle[index].life - 1.0f;
    }
    else
    {
        BufOut[index].life = 0.0f;
    }
    BufOut[index].vel = particle[index].vel;
  
}

