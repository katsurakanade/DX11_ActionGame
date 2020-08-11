#include "main.h"
#include "Renderer.h"
#include "Shader.h"
#include <io.h>

ID3D11VertexShader* Shader::mVertexShader_Default = NULL;
ID3D11PixelShader* Shader::mPixelShader_Default = NULL;

void Shader::Init(SHADER_TYPE type) {

	const char* vspass = "";
	const char* pspass = "";
	const char* cspass = "";
	const char* gspass = "";

	if (type == SHADER_TYPE::Default) {
		vspass = "vertexShader.cso";
		pspass = "pixelShader.cso";
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

		if (type == SHADER_TYPE::Default) {
			Renderer::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &mVertexShader_Default);
		}

		// 入力レイアウト生成
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		Renderer::GetDevice()->CreateInputLayout(layout,numElements,buffer,fsize, &Renderer::mVertexLayout);

		delete[] buffer;
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

		if (type == SHADER_TYPE::Default) {
			Renderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &mPixelShader_Default);
		}

		delete[] buffer;
	}

}

void Shader::Use(SHADER_TYPE type) {
	
	switch (type)
	{
	case Default:
		Renderer::GetDeviceContext()->VSSetShader(mVertexShader_Default, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(mPixelShader_Default, NULL, 0);
		break;
	default:
		break;
	}
	
}

void Shader::Uninit(SHADER_TYPE type) {

	switch (type)
	{
	case Default:
		mVertexShader_Default->Release();
		mPixelShader_Default->Release();
		break;
	default:
		break;
	}

}