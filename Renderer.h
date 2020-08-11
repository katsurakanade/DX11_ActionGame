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

struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];//16byte境界用
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
};

class Renderer
{
private:

	static D3D_FEATURE_LEVEL       mFeatureLevel;

	static ID3D11Device* mD3DDevice;
	static ID3D11DeviceContext* mImmediateContext;
	static IDXGISwapChain* mSwapChain;
	static ID3D11RenderTargetView* mRenderTargetView;
	static ID3D11DepthStencilView* mDepthStencilView;

	static ID3D11Buffer* mWorldBuffer;
	static ID3D11Buffer* mViewBuffer;
	static ID3D11Buffer* mProjectionBuffer;
	static ID3D11Buffer* mMaterialBuffer;
	static ID3D11Buffer* mLightBuffer;

	static ID3D11DepthStencilState* mDepthStateEnable;
	static ID3D11DepthStencilState* mDepthStateDisable;


public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static bool mLineMode;
	static bool mGizmosMode;
	
	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);

	static ID3D11Device* GetDevice(void) { return mD3DDevice; }
	static ID3D11DeviceContext* GetDeviceContext(void) { return mImmediateContext; }
	static ID3D11RenderTargetView* GetRenderTargetView() { return mRenderTargetView; };
	static ID3D11InputLayout* mVertexLayout;

};

