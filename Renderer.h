/*
レンダラークラス
*/

#pragma once

// 頂点構造体
struct VERTEX_3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR2 TexCoord;
};

// マテリアル構造体
struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];//16byte境界用
};

// マテリアル構造体
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture* Texture;
};

// 描画サブセット構造体
struct DX11_SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};

// ライト構造体
struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];//16byte境界用
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
};

// ブレンド状態
enum class BLEND_STATE {
	NONE,ALPHA_BLEND
};

class Renderer
{
private:

	static D3D_FEATURE_LEVEL mFeatureLevel;

	static ID3D11Device* mD3DDevice;
	static ID3D11DeviceContext* mImmediateContext;
	static IDXGISwapChain* mSwapChain;
	static ID3D11RenderTargetView* mRenderTargetView;
	static ID3D11DepthStencilView* mDepthStencilView;

	// バッファ
	static ID3D11Buffer* mWorldBuffer;
	static ID3D11Buffer* mViewBuffer;
	static ID3D11Buffer* mProjectionBuffer;
	static ID3D11Buffer* mMaterialBuffer;
	static ID3D11Buffer* mLightBuffer;
	static ID3D11Buffer* mCameraBuffer;
	static ID3D11Buffer* mParameterBuffer;

	static ID3D11DepthStencilState* mDepthStateEnable;
	static ID3D11DepthStencilState* mDepthStateDisable;

	static ID3D11BlendState* mBlendState;
	static ID3D11InputLayout* mVertexLayout;
	static ID3D11InputLayout* mVertexLayoutParticle;

public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();
		
	// 描画モード
	static bool mLineMode;
	static bool mGizmosMode;

	// バッファ生成
	static HRESULT CreateStructuredBuffer(UINT elementSize,UINT count,void* pInitData,ID3D11Buffer** ppBufferOut);
	static HRESULT CreateStructuredBuffer_DYN(UINT elementSize, UINT count, void* pInitData, ID3D11Buffer** ppBufferOut);
	static HRESULT CreateBufferSRV(ID3D11Buffer* pBuffer, ID3D11ShaderResourceView** ppSRVOut);
	static HRESULT CreateBufferUAV(ID3D11Buffer* pBuffer, ID3D11UnorderedAccessView** ppUAVOut);

	// Compute Shader
	static void RunComputeShader(ID3D11ComputeShader* pComputeShader,UINT numViews,ID3D11ShaderResourceView** pSRVs,ID3D11Buffer* pCBCS,void* pCSData,DWORD numDataBytes,ID3D11UnorderedAccessView* pUAV,UINT x,UINT y,UINT z);
	static ID3D11Buffer* CreateAndCopyToBuffer(ID3D11Buffer* pBuffer);

	// Setter
	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetCameraPosition(D3DXVECTOR3 CameraPosition);
	static void SetLight(LIGHT Light);
	static void SetParameter(D3DXVECTOR4 Parameter);
	static void SetBlendState(BLEND_STATE state);
	static void SetInputLayout(int index);

	// Getter
	static ID3D11Device* GetDevice(void) { return mD3DDevice; }
	static ID3D11DeviceContext* GetDeviceContext(void) { return mImmediateContext; }
	static ID3D11RenderTargetView* GetRenderTargetView() { return mRenderTargetView; };
	static ID3D11InputLayout** GetInputLayout() { return &mVertexLayout; };
	static ID3D11InputLayout** GetInputLayoutParticle() { return &mVertexLayoutParticle; };
};

