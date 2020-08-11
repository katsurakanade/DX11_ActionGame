#pragma once

enum SHADER_TYPE
{
	Default
};

class Shader
{
private:

	static ID3D11VertexShader* mVertexShader_Default;
	static ID3D11PixelShader* mPixelShader_Default;

public:
	static void Init(SHADER_TYPE type);
	static void Use(SHADER_TYPE type);
	static void Uninit(SHADER_TYPE type);
};

