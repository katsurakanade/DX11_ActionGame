#include "main.h"
#include "Renderer.h"
#include "Shader.h"
#include <io.h>


D3D_FEATURE_LEVEL  Renderer::mFeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Renderer::mD3DDevice = NULL;
ID3D11DeviceContext* Renderer::mImmediateContext = NULL;
IDXGISwapChain* Renderer::mSwapChain = NULL;
ID3D11RenderTargetView* Renderer::mRenderTargetView = NULL;
ID3D11DepthStencilView* Renderer::mDepthStencilView = NULL;

ID3D11InputLayout* Renderer::mVertexLayout = NULL;
ID3D11Buffer* Renderer::mWorldBuffer = NULL;
ID3D11Buffer* Renderer::mViewBuffer = NULL;
ID3D11Buffer* Renderer::mProjectionBuffer = NULL;
ID3D11Buffer* Renderer::mMaterialBuffer = NULL;
ID3D11Buffer* Renderer::mLightBuffer = NULL;

ID3D11DepthStencilState* Renderer::mDepthStateEnable = NULL;
ID3D11DepthStencilState* Renderer::mDepthStateDisable = NULL;
bool Renderer::mLineMode = false;
bool Renderer::mGizmosMode = true;

void Renderer::Init()
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���A�R���e�L�X�g����
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetWindow();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&mSwapChain,
		&mD3DDevice,
		&mFeatureLevel,
		&mImmediateContext);


	// �����_�[�^�[�Q�b�g�r���[�����A�ݒ�
	ID3D11Texture2D* pBackBuffer = NULL;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	mD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &mRenderTargetView);
	pBackBuffer->Release();

	//�X�e���V���p�e�N�X�`���[�쐬
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = sd.BufferDesc.Width;
	td.Height = sd.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc = sd.SampleDesc;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	mD3DDevice->CreateTexture2D(&td, NULL, &depthTexture);

	//�X�e���V���^�[�Q�b�g�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;
	mD3DDevice->CreateDepthStencilView(depthTexture, &dsvd, &mDepthStencilView);


	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);


	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mImmediateContext->RSSetViewports(1, &vp);

	// ���X�^���C�U�X�e�[�g�ݒ�
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	mD3DDevice->CreateRasterizerState(&rd, &rs);

	mImmediateContext->RSSetState(rs);

	// �u�����h�X�e�[�g�ݒ�
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	mD3DDevice->CreateBlendState(&blendDesc, &blendState);
	mImmediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	// �[�x�X�e���V���X�e�[�g�ݒ�
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	mD3DDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStateEnable);//�[�x�L���X�e�[�g

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	mD3DDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStateDisable);//�[�x�����X�e�[�g

	mImmediateContext->OMSetDepthStencilState(mDepthStateEnable, NULL);

	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	mD3DDevice->CreateSamplerState(&samplerDesc, &samplerState);

	mImmediateContext->PSSetSamplers(0, 1, &samplerState);

	Shader::Init(Default);
	//Shader::Init(Particle);

	// �萔�o�b�t�@����
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	mD3DDevice->CreateBuffer(&hBufferDesc, NULL, &mWorldBuffer);
	mImmediateContext->VSSetConstantBuffers(0, 1, &mWorldBuffer);

	mD3DDevice->CreateBuffer(&hBufferDesc, NULL, &mViewBuffer);
	mImmediateContext->VSSetConstantBuffers(1, 1, &mViewBuffer);

	mD3DDevice->CreateBuffer(&hBufferDesc, NULL, &mProjectionBuffer);
	mImmediateContext->VSSetConstantBuffers(2, 1, &mProjectionBuffer);


	hBufferDesc.ByteWidth = sizeof(MATERIAL);

	mD3DDevice->CreateBuffer(&hBufferDesc, NULL, &mMaterialBuffer);
	mImmediateContext->VSSetConstantBuffers(3, 1, &mMaterialBuffer);


	hBufferDesc.ByteWidth = sizeof(LIGHT);

	mD3DDevice->CreateBuffer(&hBufferDesc, NULL, &mLightBuffer);
	mImmediateContext->VSSetConstantBuffers(4, 1, &mLightBuffer);

	// ���̓��C�A�E�g�ݒ�
	mImmediateContext->IASetInputLayout(mVertexLayout);

	// �V�F�[�_�ݒ�
	Shader::Use(Default);

	// �}�e���A��������
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

}

void Renderer::Uninit()
{
	// �I�u�W�F�N�g���
	mWorldBuffer->Release();
	mViewBuffer->Release();
	mProjectionBuffer->Release();
	mLightBuffer->Release();
	mMaterialBuffer->Release();

	mVertexLayout->Release();
	Shader::Uninit(Default);

	mImmediateContext->ClearState();
	mRenderTargetView->Release();
	mSwapChain->Release();
	mImmediateContext->Release();
	mD3DDevice->Release();

}

void Renderer::Begin()
{
	// �o�b�N�o�b�t�@�N���A
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	mImmediateContext->ClearRenderTargetView(mRenderTargetView, ClearColor);

	mImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}

void Renderer::End()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	mSwapChain->Present(1, 0);
}

void Renderer::SetDepthEnable(bool Enable)
{
	if (Enable)
		mImmediateContext->OMSetDepthStencilState(mDepthStateEnable, NULL);
	else
		mImmediateContext->OMSetDepthStencilState(mDepthStateDisable, NULL);

}

void Renderer::SetWorldViewProjection2D()
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);

	mImmediateContext->UpdateSubresource(mWorldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	mImmediateContext->UpdateSubresource(mViewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&projection, &projection);
	mImmediateContext->UpdateSubresource(mProjectionBuffer, 0, NULL, &projection, 0, 0);

}

void Renderer::SetWorldMatrix(D3DXMATRIX* WorldMatrix)
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	mImmediateContext->UpdateSubresource(mWorldBuffer, 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix(D3DXMATRIX* ViewMatrix)
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	mImmediateContext->UpdateSubresource(mViewBuffer, 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix)
{
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	mImmediateContext->UpdateSubresource(mProjectionBuffer, 0, NULL, &projection, 0, 0);
}

void Renderer::SetMaterial(MATERIAL Material)
{

	mImmediateContext->UpdateSubresource(mMaterialBuffer, 0, NULL, &Material, 0, 0);

}

void Renderer::SetLight(LIGHT Light)
{

	mImmediateContext->UpdateSubresource(mLightBuffer, 0, NULL, &Light, 0, 0);

}
