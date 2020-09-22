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
ID3D11Buffer* Renderer::mCameraBuffer = NULL;

ID3D11DepthStencilState* Renderer::mDepthStateEnable = NULL;
ID3D11DepthStencilState* Renderer::mDepthStateDisable = NULL;
bool Renderer::mLineMode = false;
bool Renderer::mGizmosMode = true;

void Renderer::Init()
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーン、コンテキスト生成
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


	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	mD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &mRenderTargetView);
	pBackBuffer->Release();

	//ステンシル用テクスチャー作成
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

	//ステンシルターゲット作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;
	mD3DDevice->CreateDepthStencilView(depthTexture, &dsvd, &mDepthStencilView);


	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);


	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mImmediateContext->RSSetViewports(1, &vp);

	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	mD3DDevice->CreateRasterizerState(&rd, &rs);

	mImmediateContext->RSSetState(rs);

	// ブレンドステート設定
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

	// 深度ステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	mD3DDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	mD3DDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStateDisable);//深度無効ステート

	mImmediateContext->OMSetDepthStencilState(mDepthStateEnable, NULL);

	// サンプラーステート設定
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

	Shader::Init();

	// 定数バッファ生成
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

	hBufferDesc.ByteWidth = sizeof(D3DXVECTOR4);
	mD3DDevice->CreateBuffer(&hBufferDesc, NULL, &mCameraBuffer);
	mImmediateContext->VSSetConstantBuffers(5, 1, &mCameraBuffer);

	// 入力レイアウト設定
	mImmediateContext->IASetInputLayout(mVertexLayout);

	// シェーダ設定
	Shader::Use(SHADER_TYPE::Default);

	// マテリアル初期化
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

}

void Renderer::Uninit()
{
	// オブジェクト解放
	mWorldBuffer->Release();
	mViewBuffer->Release();
	mProjectionBuffer->Release();
	mLightBuffer->Release();
	mMaterialBuffer->Release();

	mVertexLayout->Release();
	Shader::Uninit();

	mImmediateContext->ClearState();
	mRenderTargetView->Release();
	mSwapChain->Release();
	mImmediateContext->Release();
	mD3DDevice->Release();

}

void Renderer::Begin()
{
	// バックバッファクリア
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

HRESULT Renderer::CreateStructuredBuffer(UINT elementSize,UINT count,void* pInitData,ID3D11Buffer** ppBufferOut)
{

	HRESULT hr;

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(desc));

	desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	desc.ByteWidth = elementSize * count;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = elementSize;

	if (pInitData)
	{
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = pInitData;

		hr = mD3DDevice->CreateBuffer(&desc, &initData, ppBufferOut);

		return hr;
	}

	hr = mD3DDevice->CreateBuffer(&desc, nullptr, ppBufferOut);

	return hr;
}

HRESULT Renderer::CreateStructuredBuffer_DYN(UINT elementSize, UINT count, void* pInitData, ID3D11Buffer** ppBufferOut) {
	HRESULT hr;

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(desc));

	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.ByteWidth = elementSize * count;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = elementSize;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (pInitData)
	{
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = pInitData;

		hr = mD3DDevice->CreateBuffer(&desc, &initData, ppBufferOut);

		return hr;
	}

	hr = mD3DDevice->CreateBuffer(&desc, nullptr, ppBufferOut);

	return hr;
}

HRESULT Renderer::CreateBufferSRV(ID3D11Buffer* pBuffer, ID3D11ShaderResourceView** ppSRVOut) {

	HRESULT hr;

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(desc));
	pBuffer->GetDesc(&desc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));

	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvDesc.BufferEx.FirstElement = 0;

	if (desc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS)
	{
		srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		srvDesc.BufferEx.NumElements = desc.ByteWidth / 4;
	}
	else if (desc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED)
	{
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.BufferEx.NumElements = desc.ByteWidth / desc.StructureByteStride;
	}
	else
	{
		return E_INVALIDARG;
	}

	hr = mD3DDevice->CreateShaderResourceView(pBuffer, &srvDesc, ppSRVOut);

	return hr;
}

HRESULT Renderer::CreateBufferUAV(ID3D11Buffer* pBuffer, ID3D11UnorderedAccessView** ppUAVOut) {
	
	HRESULT hr;

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(desc));
	pBuffer->GetDesc(&desc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	memset(&uavDesc, 0, sizeof(uavDesc));

	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;


	if (desc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS)
	{
		uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		uavDesc.Buffer.NumElements = desc.ByteWidth / 4;
	}
	else if (desc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED)
	{
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.Buffer.NumElements = desc.ByteWidth / desc.StructureByteStride;
	}
	else
	{
		return E_INVALIDARG;
	}

	hr = mD3DDevice->CreateUnorderedAccessView(pBuffer, &uavDesc, ppUAVOut);

	return hr;
}

void Renderer::RunComputeShader(ID3D11ComputeShader* pComputeShader, UINT numViews, ID3D11ShaderResourceView** pSRVs, ID3D11Buffer* pCBCS, void* pCSData, DWORD numDataBytes, ID3D11UnorderedAccessView* pUAV, UINT x, UINT y, UINT z) {

	mImmediateContext->CSSetShader(pComputeShader, nullptr, 0);
	mImmediateContext->CSSetShaderResources(0, numViews, pSRVs);
	mImmediateContext->CSSetUnorderedAccessViews(0, 1, &pUAV, nullptr);

	if (pCBCS)
	{
		D3D11_MAPPED_SUBRESOURCE res;

		mImmediateContext->Map(pCBCS, 0, D3D11_MAP_WRITE_DISCARD, 0, &res);
		memcpy(res.pData, pCSData, numDataBytes);
		mImmediateContext->Unmap(pCBCS, 0);

		ID3D11Buffer* ppCB[1] = { pCBCS };
		mImmediateContext->CSSetConstantBuffers(0, 1, ppCB);
	}

	mImmediateContext->Dispatch(x, y, z);

	ID3D11UnorderedAccessView* pNullUAVs[1] = { nullptr };
	ID3D11ShaderResourceView* pNullSRVs[2] = { nullptr, nullptr };
	ID3D11Buffer* pNullCBs[1] = { nullptr };

	mImmediateContext->CSSetShader(nullptr, nullptr, 0);
	mImmediateContext->CSSetUnorderedAccessViews(0, 1, pNullUAVs, nullptr);
	mImmediateContext->CSSetShaderResources(0, 2, pNullSRVs);
	mImmediateContext->CSSetConstantBuffers(0, 1, pNullCBs);
}

ID3D11Buffer* Renderer::CreateAndCopyToBuffer(ID3D11Buffer* pBuffer)
{
	ID3D11Buffer* pCloneBuf = nullptr;

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(desc));

	pBuffer->GetDesc(&desc);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.MiscFlags = 0;

	mD3DDevice->CreateBuffer(&desc, nullptr, &pCloneBuf);
	mImmediateContext->CopyResource(pCloneBuf, pBuffer);

	return pCloneBuf;

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

void Renderer::SetCameraPosition(D3DXVECTOR3 CameraPosition)
{
	mImmediateContext->UpdateSubresource(mCameraBuffer, 0, NULL, &D3DXVECTOR4(CameraPosition.x, CameraPosition.y, CameraPosition.z, 1.0f), 0, 0);
}

void Renderer::SetLight(LIGHT Light)
{

	mImmediateContext->UpdateSubresource(mLightBuffer, 0, NULL, &Light, 0, 0);

}
