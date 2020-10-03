/*
�V�F�[�_�[�N���X
*/

#pragma once

#define SHADER_MAX 2

enum class SHADER_TYPE
{
	SkinMesh,Particle
};

enum class SHADER_TYPE_VSPS {
	Default,Unlit
};

class Shader
{
private:

	// ���_�V�F�[�_�[
	static std::vector < ID3D11VertexShader*> mVertexShaderArray;
	// �s�N�Z���V�F�[�_�[
	static std::vector < ID3D11PixelShader*> mPixelShaderArray;
	// �v�Z�V�F�[�_�[
	static std::vector < ID3D11ComputeShader*> mComputeShaderArray;

	// �V�F�[�_�[����
	static void CreateVertexShader(SHADER_TYPE_VSPS type);
	static void CreatePixelShader(SHADER_TYPE_VSPS type);
	static void CreateComputeShader(SHADER_TYPE type);

public:

	static void Init();
	static void Uninit();

	// �g�p�iVS+PS�j
	static void Use(SHADER_TYPE_VSPS type);
	// Getter
	static std::vector < ID3D11ComputeShader*> GetComputeShaderArray() { return mComputeShaderArray; };
};

