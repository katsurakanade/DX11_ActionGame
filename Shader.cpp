#include "main.h"
#include "Renderer.h"
#include "Shader.h"
#include <io.h>

ID3D11VertexShader* Shader::VertexShader_Default = NULL;
ID3D11PixelShader* Shader::PixelShader_Default = NULL;

ID3D11VertexShader* Shader::VertexShader_Particle = NULL;
ID3D11PixelShader* Shader::PixelShader_Particle = NULL;
ID3D11ComputeShader* Shader::ComputeShader_Particle = NULL;
ID3D11GeometryShader* Shader::GeometryShader_Particle = NULL;

void Shader::Init(SHADER_TYPE type) {

	const char* vspass = "";
	const char* pspass = "";
	const char* cspass = "";
	const char* gspass = "";

	if (type == SHADER_TYPE::Default) {
		vspass = "vertexShader.cso";
		pspass = "pixelShader.cso";
	}

	else if (type == SHADER_TYPE::Particle) {
		vspass = "vertexShader.cso";
		pspass = "particlePS.cso";
		cspass = "particleCS.cso";
		gspass = "particleGS.cso";
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
			Renderer::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &VertexShader_Default);
		}

		else if (type == SHADER_TYPE::Particle) {
			Renderer::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &VertexShader_Particle);
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

		Renderer::GetDevice()->CreateInputLayout(layout,numElements,buffer,fsize, &Renderer::m_VertexLayout);

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
			Renderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &PixelShader_Default);
		}

		else if (type == SHADER_TYPE::Particle) {
			Renderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &PixelShader_Particle);
		}

		delete[] buffer;
	}

	if (cspass != "") {
		FILE* file;
		long int fsize;

		file = fopen(cspass, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		Renderer::GetDevice()->CreateComputeShader(buffer, fsize, NULL, &ComputeShader_Particle);

		delete[] buffer;
	}

	if (gspass != "") {
		FILE* file;
		long int fsize;

		file = fopen(gspass, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		Renderer::GetDevice()->CreateGeometryShader(buffer, fsize, NULL, &GeometryShader_Particle);

		delete[] buffer;
	}
}

void Shader::Use(SHADER_TYPE type) {
	
	switch (type)
	{
	case Default:
		Renderer::GetDeviceContext()->VSSetShader(VertexShader_Default, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(PixelShader_Default, NULL, 0);
		break;
	default:
		break;
	}
	
}

void Shader::Uninit(SHADER_TYPE type) {

	switch (type)
	{
	case Default:
		VertexShader_Default->Release();
		PixelShader_Default->Release();
		break;
	default:
		break;
	}

}