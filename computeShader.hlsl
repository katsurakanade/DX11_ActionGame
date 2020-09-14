//------------------------------------------------------------------------------------
// File : BasicCompute.hlsl
// Desc : Sample Compute Shader.
// Copyright(c) Project Asura. All right reserved.
//------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////
// BufType structure
//////////////////////////////////////////////////////////////////////////////////////
struct BufType
{
    int i; //!< int�̒l���i�[.
};


///////////////////////////////////////////////////////////////////////////////////////
// CSInput structure
///////////////////////////////////////////////////////////////////////////////////////
struct CSInput
{
    uint3 groupThread : SV_GroupThreadID;
    uint3 group : SV_GroupID;
    uint groupIndex : SV_GroupIndex;
    uint3 dispatch : SV_DispatchThreadID;
};


//------------------------------------------------------------------------------------
// Structured Buffers
//------------------------------------------------------------------------------------
StructuredBuffer<BufType> BufIn0 : register(t0); //!< ���͗p.
StructuredBuffer<BufType> BufIn1 : register(t1); //!< ���͗p.
RWStructuredBuffer<BufType> BufOut : register(u0); //!< �o�͗p.


#define size_x      1024
#define size_y      1
#define size_z      1


//------------------------------------------------------------------------------------
//      �R���s���[�g�V�F�[�_�̃��C���G���g���[�|�C���g�ł�.
//------------------------------------------------------------------------------------
[numthreads(size_x, size_y, size_z)]
void CSFunc(const CSInput input)
{
    int index = input.dispatch.x;

    // �K���ɉ��Z�����Ă݂�.
    BufOut[index].i = BufIn0[index].i + BufIn1[index].i;
}
