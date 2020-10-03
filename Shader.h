/*
シェーダークラス
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

	// 頂点シェーダー
	static std::vector < ID3D11VertexShader*> mVertexShaderArray;
	// ピクセルシェーダー
	static std::vector < ID3D11PixelShader*> mPixelShaderArray;
	// 計算シェーダー
	static std::vector < ID3D11ComputeShader*> mComputeShaderArray;

	// シェーダー生成
	static void CreateVertexShader(SHADER_TYPE_VSPS type);
	static void CreatePixelShader(SHADER_TYPE_VSPS type);
	static void CreateComputeShader(SHADER_TYPE type);

public:

	static void Init();
	static void Uninit();

	// 使用（VS+PS）
	static void Use(SHADER_TYPE_VSPS type);
	// Getter
	static std::vector < ID3D11ComputeShader*> GetComputeShaderArray() { return mComputeShaderArray; };
};

