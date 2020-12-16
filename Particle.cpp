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
	std::uniform_real_distribution<float> rndtheta(-3.14f, 3.14f);

	VERTEX_3D_PARTICLE vertex[4];

	vertex[0].Position = D3DXVECTOR3(-setting->Size, setting->Size, 0.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(setting->Size, setting->Size, 0.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-setting->Size, -setting->Size, 0.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(setting->Size, -setting->Size, 0.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	// パーティクル資料生成
	mParticleAmount = setting->Amount;
	mParticleLifeMax = (int)setting->LifeMinMax.y;
	mparticle = new ParticleCompute[setting->Amount];

	for (int i = 0; i < setting->Amount; i++) {
		if (setting->RandomSpeed) {
			if (setting->PolarCoordinates) {
				auto x = rndvelX(Application::RandomGen);
				auto y = rndvelY(Application::RandomGen);
				auto z = rndvelZ(Application::RandomGen);
				auto radius = sqrt(x * x + y * y + z * z);
				auto theta = rndtheta(Application::RandomGen);
				auto phi = 3.14f;

				x = radius * sin(theta) * cos(phi);
				y = radius * sin(theta) * sin(phi);
				z = radius * cos(theta);

				mparticle[i].vel = D3DXVECTOR3(x, z, y);
			}
			else {
				mparticle[i].vel = D3DXVECTOR3(rndvelX(Application::RandomGen), rndvelY(Application::RandomGen), rndvelZ(Application::RandomGen));
			}
		}
		mparticle[i].life = rndlife(Application::RandomGen);
		mparticle[i].pos = setting->Position + D3DXVECTOR3(rndposX(Application::RandomGen), rndposY(Application::RandomGen), rndposZ(Application::RandomGen));
		mparticle[i].col = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D_PARTICLE) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ComputeShader用のデータ生成
	CreateComputeResource();

}

void ParticleSystem::Uninit() {

	delete mparticle;
	mparticle = nullptr;

	// バッファリリース
	mVertexBuffer->Release();
	mpParticleBuffer->Release();
	mpTimeBuffer->Release();
	mpResultBuffer->Release();
	mpPositionBuffer->Release();
	mpLifeBuffer->Release();
	// SRVリリース
	mpParticleSRV->Release();
	mpResultUAV->Release();
	mpPositionSRV->Release();
	mpLifeSRV->Release();
	// UAVリリース
	mpResultUAV->Release();
}

void ParticleSystem::CreateComputeResource() {

	HRESULT hr;

	// Input
	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(ParticleCompute), (UINT)mParticleAmount, nullptr, &mpParticleBuffer);
	assert(SUCCEEDED(hr));

	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(TimeCompute), (UINT)mParticleAmount, nullptr, &mpTimeBuffer);
	assert(SUCCEEDED(hr));

	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(D3DXVECTOR3), (UINT)mParticleAmount, nullptr, &mpPositionBuffer);
	assert(SUCCEEDED(hr));

	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(float), (UINT)mParticleAmount, nullptr, &mpLifeBuffer);
	assert(SUCCEEDED(hr));

	// SRV
	hr = Renderer::CreateBufferSRV(mpParticleBuffer, &mpParticleSRV);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateBufferSRV(mpTimeBuffer, &mpTimeSRV);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateBufferSRV(mpPositionBuffer, &mpPositionSRV);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateBufferSRV(mpLifeBuffer, &mpLifeSRV);
	assert(SUCCEEDED(hr));

	// Output
	hr = Renderer::CreateStructuredBuffer(sizeof(ParticleCompute), (UINT)mParticleAmount, nullptr, &mpResultBuffer);
	assert(SUCCEEDED(hr));

	// UAV
	hr = Renderer::CreateBufferUAV(mpResultBuffer, &mpResultUAV);
	assert(SUCCEEDED(hr));


}

void ParticleSystem::Update() {

	// Fill Data (Performance Issues)
	{
		D3D11_MAPPED_SUBRESOURCE subRes;
		Renderer::GetDeviceContext()->Map(mpParticleBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		ParticleCompute* pBufType = (ParticleCompute*)subRes.pData;
		memcpy(subRes.pData, mparticle, sizeof(ParticleCompute) * mParticleAmount);
		Renderer::GetDeviceContext()->Unmap(mpParticleBuffer, 0);
	}

	// Fill Time
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

	// CopyResource
	{
		ID3D11Buffer* pBufDbg = Renderer::CreateAndCopyToBuffer(mpResultBuffer);
		D3D11_MAPPED_SUBRESOURCE subRes;

		Renderer::GetDeviceContext()->Map(pBufDbg, 0, D3D11_MAP_READ, 0, &subRes);
		ParticleCompute* pBufType = (ParticleCompute*)subRes.pData;
		memcpy(mparticle, pBufType, sizeof(ParticleCompute) * mParticleAmount);
		Renderer::GetDeviceContext()->Unmap(pBufDbg, 0);

		pBufDbg->Release();
	}

	// Fiil Position To PositionBuffer
	{
		D3D11_MAPPED_SUBRESOURCE subRes;
		Renderer::GetDeviceContext()->Map(mpPositionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		D3DXVECTOR3* pBufType = (D3DXVECTOR3*)subRes.pData;
		for (int v = 0; v < mParticleAmount; v++) {
			pBufType[v] = mparticle[v].pos;
		}
		Renderer::GetDeviceContext()->Unmap(mpPositionBuffer, 0);
	}

	{
		D3D11_MAPPED_SUBRESOURCE subRes;
		Renderer::GetDeviceContext()->Map(mpLifeBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		float* pBufType = (float*)subRes.pData;
		for (int v = 0; v < mParticleAmount; v++) {
			pBufType[v] = mparticle[v].life;
		}
		Renderer::GetDeviceContext()->Unmap(mpLifeBuffer, 0);
	}

	// Kill
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
	Renderer::SetInputLayout(1);

	UINT stride = sizeof(VERTEX_3D_PARTICLE);
	UINT offset = 0;

	Shader::Use(SHADER_TYPE_VSPS::Particle);

	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture);

	Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &mpPositionSRV);

	Renderer::GetDeviceContext()->VSSetShaderResources(3, 1, &mpLifeSRV);

	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::GetDeviceContext()->DrawInstanced(4, mParticleAmount, 0, 0);

	Renderer::SetInputLayout(0);

}