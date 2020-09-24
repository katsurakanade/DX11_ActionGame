#pragma once

#define SHADER_MAX 2

enum class SHADER_TYPE
{
	Default,SkinMesh,Particle
};

enum class SHADER_TYPE_VSPS {
	Default,Unlit
};

class Shader
{
private:

	static std::vector < ID3D11VertexShader *> mVertexShaderArray;
	static std::vector < ID3D11PixelShader*> mPixelShaderArray;
	static std::vector < ID3D11ComputeShader*> mComputeShaderArray;

	static void CreateVertexShader(SHADER_TYPE_VSPS type);
	static void CreatePixelShader(SHADER_TYPE_VSPS type);
	static void CreateComputeShader(SHADER_TYPE type);

public:
	static void Init();
	static void Uninit();
	static void Use(SHADER_TYPE_VSPS type);

	static std::vector < ID3D11ComputeShader*> GetComputeShaderArray() { return mComputeShaderArray; };
};

