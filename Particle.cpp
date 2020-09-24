#include "main.h"
#include "Renderer.h"
#include "Particle.h"
#include "Application.h"
#include "Scene.h"
#include "input.h"
#include <random>
#include "Shader.h"

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());
std::uniform_real_distribution<float> dis(0.1f, 0.5f);
std::uniform_real_distribution<float> dis2(-1.0f, 1.0f);

void ParticleSystem::Init() {

	float col[4];

	for (int i = 0; i < MAX_PARTICLE; i++) {
		mVel[i] = D3DXVECTOR3(dis2(gen), dis(gen), dis2(gen));
		mparticle[i].vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		mparticle[i].vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		mparticle[i].vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		mparticle[i].vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		mparticle[i].vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		mparticle[i].vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		mparticle[i].vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		mparticle[i].vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		mparticle[i].vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		mparticle[i].vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		mparticle[i].vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		mparticle[i].vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		mparticle[i].vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		mparticle[i].vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		mparticle[i].vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		mparticle[i].vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	}

	col[0] = 1;
	col[1] = 1;
	col[2] = 1;
	col[3] = 1;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Particle) * MAX_PARTICLE;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mparticle;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

	D3D11_BUFFER_DESC cbd;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(float) * 4;
	cbd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;

	sd.pSysMem = col;

	Renderer::GetDevice()->CreateBuffer(&cbd, &sd, &mColorBuffer);

	mTexture = Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE);

	Position = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	CreateComputeResource();

}

void ParticleSystem::Uninit() {
	mVertexBuffer->Release();
	mColorBuffer->Release();
}

void ParticleSystem::CreateComputeResource(){

	HRESULT hr;

	// Input
	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(ParticleCompute), (UINT)MAX_PARTICLE, nullptr, &mpParticleBuffer);
	assert(SUCCEEDED(hr));

	// SRV
	hr = Renderer::CreateBufferSRV(mpParticleBuffer, &mpParticleSRV);
	assert(SUCCEEDED(hr)); 
	
	// Output
	hr = Renderer::CreateStructuredBuffer(sizeof(ParticleCompute), (UINT)MAX_PARTICLE, nullptr, &mpResultBuffer);
	assert(SUCCEEDED(hr));

	// UAV
	hr = Renderer::CreateBufferUAV(mpResultBuffer, &mpResultUAV);
	assert(SUCCEEDED(hr));
}

void ParticleSystem::Update() {

	//// Fill Data
	//D3D11_MAPPED_SUBRESOURCE subRes;
	//Renderer::GetDeviceContext()->Map(mpParticleBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
	//ParticleCompute* pBufType = (ParticleCompute*)subRes.pData;
	//for (unsigned int v = 0; v < MAX_PARTICLE; v++) {
	//	pBufType[v].pos[0] = mparticle[v].vertex[0].Position;
	//	pBufType[v].pos[1] = mparticle[v].vertex[1].Position;
	//	pBufType[v].pos[2] = mparticle[v].vertex[2].Position;
	//	pBufType[v].pos[3] = mparticle[v].vertex[3].Position;
	//}
	//Renderer::GetDeviceContext()->Unmap(mpParticleBuffer, 0);

	//ID3D11ShaderResourceView* pSRVs[1] = { mpParticleSRV };
	//Renderer::GetDeviceContext()->CSSetShaderResources(0, 1, pSRVs);
	//Renderer::GetDeviceContext()->CSSetShader(Shader::GetComputeShaderArray()[2], nullptr, 0);
	//Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &mpResultUAV, 0);

	//Renderer::GetDeviceContext()->Dispatch(1024, 1, 1);

	//ID3D11Buffer* pBufDbg;
	//D3D11_BUFFER_DESC desc;
	//memset(&desc, 0, sizeof(desc));
	//mpResultBuffer->GetDesc(&desc);
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	//desc.Usage = D3D11_USAGE_STAGING;
	//desc.BindFlags = 0;
	//desc.MiscFlags = 0;
	//Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &pBufDbg);
	//Renderer::GetDeviceContext()->CopyResource(pBufDbg, mpResultBuffer);

	//{
	//	D3D11_MAPPED_SUBRESOURCE subRes;
	//	ParticleCompute* pBufType;
	//	Renderer::GetDeviceContext()->Map(pBufDbg, 0, D3D11_MAP_READ, 0, &subRes);
	//	pBufType = (ParticleCompute*)subRes.pData;

	//	{
	//		D3D11_MAPPED_SUBRESOURCE ms;
	//		Renderer::GetDeviceContext()->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
	//		Particle* particle = (Particle*)ms.pData;

	//		for (unsigned int v = 0; v < MAX_PARTICLE; v++) {
	//			particle[v].vertex[0].Position = pBufType[v].pos[0];
	//			particle[v].vertex[1].Position = pBufType[v].pos[1];
	//			particle[v].vertex[2].Position = pBufType[v].pos[2];
	//			particle[v].vertex[3].Position = pBufType[v].pos[3];
	//			DebugOutputString(std::to_string(pBufType[v].pos[0].y).c_str());
	//		}

	//		Renderer::GetDeviceContext()->Unmap(mVertexBuffer, 0);
	//	}

	//	Renderer::GetDeviceContext()->Unmap(pBufDbg, 0);
	//	pBufDbg->Release();

	//}

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	Particle* vertex = (Particle*)msr.pData;

	for (int i = 0; i < MAX_PARTICLE; i++) {

		for (int k = 0; k < 4; k++)
		{
			vertex[i].vertex[k].Position += mVel[i];
		}
	}

	Renderer::GetDeviceContext()->Unmap(mVertexBuffer, 0);

}

void ParticleSystem::Render() {

	// BillBoard
	Camera* camera = Application::GetScene()->GetGameObject<Camera>(CameraLayer);
	D3DXMATRIX view = camera->GetViewMatrix();
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	D3DXMATRIX world, scale, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * invView * trans;

	Renderer::SetWorldMatrix(&world);

	Renderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &mColorBuffer);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture);

	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	for (int i = 0; i < MAX_PARTICLE; i++) {
		Renderer::GetDeviceContext()->Draw(4, 0 + (i*4));
	}

}