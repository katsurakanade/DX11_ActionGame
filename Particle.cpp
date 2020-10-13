#include "main.h"
#include "Renderer.h"
#include "Particle.h"
#include "Application.h"
#include "Scene.h"
#include "input.h"
#include <random>
#include "Shader.h"


void ParticleSystem::Init() {
	
	mKillFrame = 0.0f;

	Name = "ParticleSystem";

}

void ParticleSystem::Create(ParitcleSetting* setting) {

	std::uniform_real_distribution<float> rndposX(setting->PostionMinMaxX.x, setting->PostionMinMaxX.y);
	std::uniform_real_distribution<float> rndposY(setting->PostionMinMaxY.x, setting->PostionMinMaxY.y);
	std::uniform_real_distribution<float> rndposZ(setting->PostionMinMaxZ.x, setting->PostionMinMaxZ.y);
	std::uniform_real_distribution<float> rndvelX(setting->SpeedMinMaxX.x, setting->SpeedMinMaxX.y);
	std::uniform_real_distribution<float> rndvelY(setting->SpeedMinMaxY.x, setting->SpeedMinMaxY.y);
	std::uniform_real_distribution<float> rndvelZ(setting->SpeedMinMaxZ.x, setting->SpeedMinMaxZ.y);
	std::uniform_real_distribution<float> rndlife(setting->LifeMinMax.x, setting->LifeMinMax.y);

	// パーティクル資料生成
	mParticleAmount = setting->Amount;
	mParticleLifeMax = setting->LifeMinMax.y;
	mparticle = new Particle[setting->Amount];
	mVel = new D3DXVECTOR3[setting->Amount];
	mlife = new float[setting->Amount];
	mParticlePos = new D3DXVECTOR3[setting->Amount];

	for (int i = 0; i < setting->Amount; i++) {

		if (setting->RandomSpeed) {
			mVel[i] = D3DXVECTOR3(rndvelX(Application::RandomGen), rndvelY(Application::RandomGen), rndvelZ(Application::RandomGen));
		}

		else if (!setting->RandomSpeed) {
			mVel[i] = D3DXVECTOR3(setting->Speed.x, setting->Speed.y, setting->Speed.z);
		}

		mlife[i] = rndlife(Application::RandomGen);

		D3DXVECTOR3 pos = Position + D3DXVECTOR3(rndposX(Application::RandomGen), rndposY(Application::RandomGen), rndposZ(Application::RandomGen));

		mparticle[i].vertex[0].Position = pos  + D3DXVECTOR3(-setting->Size, setting->Size, 0.0f);
		mparticle[i].vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		mparticle[i].vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		mparticle[i].vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		mparticle[i].vertex[1].Position = pos + D3DXVECTOR3(setting->Size, setting->Size, 0.0f);
		mparticle[i].vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		mparticle[i].vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		mparticle[i].vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		mparticle[i].vertex[2].Position = pos + D3DXVECTOR3(-setting->Size, -setting->Size, 0.0f);
		mparticle[i].vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		mparticle[i].vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		mparticle[i].vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		mparticle[i].vertex[3].Position = pos + D3DXVECTOR3(setting->Size, -setting->Size, 0.0f);
		mparticle[i].vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		mparticle[i].vertex[3].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
		mparticle[i].vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		mParticlePos[i] = pos;
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Particle) * setting->Amount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mparticle;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

	mTexture = Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE);

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ComputeShader用のデータ生成
	CreateComputeResource();
}

void ParticleSystem::Uninit() {

	delete mparticle;
	mparticle = nullptr;

	delete mVel;
	mVel = nullptr;
	
	delete mlife;
	mlife = nullptr;

	delete mParticlePos;
	mParticlePos = nullptr;

	mVertexBuffer->Release();
	mpParticleBuffer->Release();
	mpResultBuffer->Release();
	mpParticleSRV->Release();
	mpResultUAV->Release();
}

void ParticleSystem::CreateComputeResource(){

	HRESULT hr;

	// Input
	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(ParticleCompute), (UINT)mParticleAmount, nullptr, &mpParticleBuffer);
	assert(SUCCEEDED(hr));

	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(TimeCompute), (UINT)mParticleAmount, nullptr, &mpTimeBuffer);
	assert(SUCCEEDED(hr));

	// SRV
	hr = Renderer::CreateBufferSRV(mpParticleBuffer, &mpParticleSRV);
	assert(SUCCEEDED(hr)); 
	hr = Renderer::CreateBufferSRV(mpTimeBuffer, &mpTimeSRV);
	assert(SUCCEEDED(hr));
	
	// Output
	hr = Renderer::CreateStructuredBuffer(sizeof(ParticleCompute), (UINT)mParticleAmount, nullptr, &mpResultBuffer);
	assert(SUCCEEDED(hr));

	// UAV
	hr = Renderer::CreateBufferUAV(mpResultBuffer, &mpResultUAV);
	assert(SUCCEEDED(hr));
}

void ParticleSystem::Update() {

	// Fill Data
	{
		D3D11_MAPPED_SUBRESOURCE subRes;
		Renderer::GetDeviceContext()->Map(mpParticleBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		ParticleCompute* pBufType = (ParticleCompute*)subRes.pData;
		for (int v = 0; v < mParticleAmount; v++) {
			pBufType[v].vel = mVel[v];
			pBufType[v].col = mparticle[v].vertex[0].Diffuse;
			pBufType[v].life = mlife[v];
			pBufType[v].pos[0] = mparticle[v].vertex[0].Position;
			pBufType[v].pos[1] = mparticle[v].vertex[1].Position;
			pBufType[v].pos[2] = mparticle[v].vertex[2].Position;
			pBufType[v].pos[3] = mparticle[v].vertex[3].Position;
		}
		Renderer::GetDeviceContext()->Unmap(mpParticleBuffer, 0);
	}

	{
		D3D11_MAPPED_SUBRESOURCE subRes;
		Renderer::GetDeviceContext()->Map(mpTimeBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		TimeCompute* pBufType = (TimeCompute*)subRes.pData;
		for (int v = 0; v < mParticleAmount; v++) {
			pBufType[v].DeltaTime = Time::GetDeltaTime();
			pBufType[v].Time = mKillFrame;
		}
		Renderer::GetDeviceContext()->Unmap(mpTimeBuffer, 0);
	}

	// Compute
	ID3D11ShaderResourceView* pSRVs[2] = { mpParticleSRV,mpTimeSRV };
	Renderer::GetDeviceContext()->CSSetShaderResources(0, 2, pSRVs);
	Renderer::GetDeviceContext()->CSSetShader(Shader::GetComputeShaderArray()[1], nullptr, 0);
	Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &mpResultUAV, 0);
	Renderer::GetDeviceContext()->Dispatch(1024, 1, 1);

	ID3D11Buffer* pBufDbg;
	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(desc));
	mpResultBuffer->GetDesc(&desc);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.MiscFlags = 0;
	Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &pBufDbg);
	Renderer::GetDeviceContext()->CopyResource(pBufDbg, mpResultBuffer);

	// Return Resource
	{
		D3D11_MAPPED_SUBRESOURCE subRes;
		Renderer::GetDeviceContext()->Map(pBufDbg, 0, D3D11_MAP_READ, 0, &subRes);
		ParticleCompute* pBufType = (ParticleCompute*)subRes.pData;

		for (int v = 0; v < mParticleAmount; v++) {
			mparticle[v].vertex[0].Position = pBufType[v].pos[0];
			mparticle[v].vertex[1].Position = pBufType[v].pos[1];
			mparticle[v].vertex[2].Position = pBufType[v].pos[2];
			mparticle[v].vertex[3].Position = pBufType[v].pos[3];
			mlife[v] = pBufType[v].life;
		}

		{
			D3D11_MAPPED_SUBRESOURCE ms;
			Renderer::GetDeviceContext()->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
			Particle* particle = (Particle*)ms.pData;

			for (int v = 0; v < mParticleAmount; v++) {

				particle[v].vertex[0].Position = mparticle[v].vertex[0].Position;
				particle[v].vertex[1].Position = mparticle[v].vertex[1].Position;
				particle[v].vertex[2].Position = mparticle[v].vertex[2].Position;
				particle[v].vertex[3].Position = mparticle[v].vertex[3].Position;

				particle[v].vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				particle[v].vertex[0].Diffuse = pBufType[v].col;
				particle[v].vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

				particle[v].vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				particle[v].vertex[1].Diffuse = pBufType[v].col;
				particle[v].vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

				particle[v].vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				particle[v].vertex[2].Diffuse = pBufType[v].col;
				particle[v].vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

				particle[v].vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				particle[v].vertex[3].Diffuse = pBufType[v].col;
				particle[v].vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
				
			}

			Renderer::GetDeviceContext()->Unmap(mVertexBuffer, 0);
		}

		Renderer::GetDeviceContext()->Unmap(pBufDbg, 0);
		pBufDbg->Release();

	}

	mKillFrame += 1.0f;

	if (mKillFrame > mParticleLifeMax) {
		this->Destroy();
	}

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

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture);

	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Shader::Use(SHADER_TYPE_VSPS::Unlit);	

	for (int i = 0; i < mParticleAmount; i++) {
		if (mlife[i] > 0.0f) {
			Renderer::GetDeviceContext()->Draw(4, 0 + (i * 4));	Renderer::GetDeviceContext()->Draw(4, 0 + (i * 4));
		}
	}

}