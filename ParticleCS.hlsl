struct ParticleCompute
{
    float3 vertex[4];
    float3 vel;
    float life;
};

struct CSInput
{
    uint3 groupThread : SV_GroupThreadID;
    uint3 group : SV_GroupID;
    uint groupIndex : SV_GroupIndex;
    uint3 dispatch : SV_DispatchThreadID;
};

StructuredBuffer<ParticleCompute> particle : register(t0);
RWStructuredBuffer<ParticleCompute> BufOut : register(u0);

#define size_x      512
#define size_y      1
#define size_z      1

[numthreads(size_x, size_y, size_z)]
void CSFunc(const CSInput input)
{
    int index = input.dispatch.x;
    
    float3 result[4];
    result[0] = particle[index].vertex[0] + particle[index].vel;
    result[1] = particle[index].vertex[1] + particle[index].vel;
    result[2] = particle[index].vertex[2] + particle[index].vel;
    result[3] = particle[index].vertex[3] + particle[index].vel;
    
   float alife =  particle[index].life - 1.0f;
    
    BufOut[index].vertex[0] = result[0];
    BufOut[index].vertex[1] = result[1];
    BufOut[index].vertex[2] = result[2];
    BufOut[index].vertex[3] = result[3];
    BufOut[index].life = alife;

  
}

