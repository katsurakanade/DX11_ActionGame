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
	mComputeShaderArray.resize(SHADER_MAX);

	CreateVertexShader(SHADER_TYPE::Default);
	CreatePixelShader(SHADER_TYPE::Default);
	CreateComputeShader(SHADER_TYPE::Default);
}

void Shader::Uninit() {

	for (ID3D11VertexShader* v : mVertexShaderArray) {
		v->Release();
	}

	for (ID3D11PixelShader* p : mPixelShaderArray) {
		p->Release();
	}

	std::vector<ID3D11VertexShader*>().swap(mVertexShaderArray);
	std::vector<ID3D11PixelShader*>().swap(mPixelShaderArray);
}

void Shader::Use(SHADER_TYPE type) {

	Renderer::GetDeviceContext()->VSSetShader(mVertexShaderArray[(int)type], NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(mPixelShaderArray[(int)type], NULL, 0);

}

void Shader::CreateVertexShader(SHADER_TYPE type) {

	const char* vspass = "";

	if (type == SHADER_TYPE::Default) {
		vspass = "vertexShader.cso";
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

void Shader::CreatePixelShader(SHADER_TYPE type) {
	const char* pspass = "";

	if (type == SHADER_TYPE::Default) {
		pspass = "pixelShader.cso";
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

	if (type == SHADER_TYPE::Default) {
		cspass = "computeShader.cso";
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