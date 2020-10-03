#include "main.h"
#include "Renderer.h"
#include "Shader.h"
#include <io.h>

std::vector < ID3D11VertexShader*> Shader::mVertexShaderArray;
std::vector < ID3D11PixelShader*> Shader::mPixelShaderArray;
std::vector < ID3D11ComputeShader*> Shader::mComputeShaderArray;

void Shader::Init() {

	mVertexShaderArray.resize(SHADER_MAX);
	mPixelShaderArray.resize(SHADER_MAX);
	mComputeShaderArray.resize(2);

	CreateVertexShader(SHADER_TYPE_VSPS::Default);
	CreatePixelShader(SHADER_TYPE_VSPS::Default);
	CreateVertexShader(SHADER_TYPE_VSPS::Unlit);
	CreatePixelShader(SHADER_TYPE_VSPS::Unlit);

	CreateComputeShader(SHADER_TYPE::SkinMesh);
	CreateComputeShader(SHADER_TYPE::Particle);
}

void Shader::Uninit() {

	for (ID3D11VertexShader* v : mVertexShaderArray) {
		v->Release();
	}

	for (ID3D11PixelShader* p : mPixelShaderArray) {
		p->Release();
	}

	for (ID3D11ComputeShader* p : mComputeShaderArray) {
		p->Release();
	}

	std::vector<ID3D11VertexShader*>().swap(mVertexShaderArray);
	std::vector<ID3D11PixelShader*>().swap(mPixelShaderArray);
	std::vector<ID3D11ComputeShader*>().swap(mComputeShaderArray);
}

void Shader::Use(SHADER_TYPE_VSPS type) {

	Renderer::GetDeviceContext()->VSSetShader(mVertexShaderArray[(int)type], NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(mPixelShaderArray[(int)type], NULL, 0);

}

void Shader::CreateVertexShader(SHADER_TYPE_VSPS type) {

	const char* vspass = "";

	if (type == SHADER_TYPE_VSPS::Default) {
		vspass = "vertexShader.cso";
	}
	else if (type == SHADER_TYPE_VSPS::Unlit) {
		vspass = "UnlitVS.cso";
	}

	// 頂点シェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(vspass, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		Renderer::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &mVertexShaderArray[int(type)]);

		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		Renderer::GetDevice()->CreateInputLayout(layout, numElements, buffer, fsize, &Renderer::mVertexLayout);

		delete[] buffer;
	}

}

void Shader::CreatePixelShader(SHADER_TYPE_VSPS type) {
	const char* pspass = "";

	if (type == SHADER_TYPE_VSPS::Default) {
		pspass = "pixelShader.cso";
	}
	else if (type == SHADER_TYPE_VSPS::Unlit) {
		pspass = "UnlitPS.cso";
	}

	// ピクセルシェーダ生成
	{
		FILE* file;
		long int fsize;

		file = fopen(pspass, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		Renderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &mPixelShaderArray[int(type)]);

		delete[] buffer;
	}
}

void Shader::CreateComputeShader(SHADER_TYPE type) {

	const char* cspass = "";

	if (type == SHADER_TYPE::SkinMesh) {
		cspass = "MeshAnimationCS.cso";
	}
	else if (type == SHADER_TYPE::Particle) {
		cspass = "ParticleCS.cso";
	}

	FILE* file;
	long int fsize;

	file = fopen(cspass, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	Renderer::GetDevice()->CreateComputeShader(buffer, fsize, nullptr, &mComputeShaderArray[int(type)]);

	delete[] buffer;

}