#pragma once

enum SHADER_TYPE
{
	Default,Particle
};

class Shader
{
private:

	static ID3D11VertexShader* VertexShader_Default;
	static ID3D11PixelShader* PixelShader_Default;

	static ID3D11VertexShader* VertexShader_Particle;
	static ID3D11PixelShader* PixelShader_Particle;
	static ID3D11ComputeShader* ComputeShader_Particle;
	static ID3D11GeometryShader* GeometryShader_Particle;

public:
	static void Init(SHADER_TYPE type);
	static void Use(SHADER_TYPE type);
	static void Uninit(SHADER_TYPE type);
};

