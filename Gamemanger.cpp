#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Scene.h"
#include "Gamemanger.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Player.h"
#include "StaticManger.h"
#include "Shader.h"

void Gamemanger::Init() {

	Name = "GameManger";
	mRound = 0;

	mpLevel = Application::GetScene()->GetGameObject<Level>(ObjectLayer);

	for (int i = 0; i < 16; i++) {
		mBuf_0[i].s32 = i;
		mBuf_1[i].s32 = i;
	}

	// Compute Test
	HRESULT hr;

	hr = Renderer::CreateStructuredBuffer(sizeof(BufType), 16, &mBuf_0[0], &mpBuf_0);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateStructuredBuffer(sizeof(BufType), 16, &mBuf_1[0], &mpBuf_1);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateStructuredBuffer(sizeof(BufType), 16, nullptr, &mpBufResult);
	assert(SUCCEEDED(hr));

	hr = Renderer::CreateBufferSRV(mpBuf_0, &mpBufSRV0);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateBufferSRV(mpBuf_1, &mpBufSRV1);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateBufferUAV(mpBufResult, &mpBufUAV);
	assert(SUCCEEDED(hr));

	ID3D11ShaderResourceView* pSRVs[2] = { mpBufSRV0, mpBufSRV1 };
	Renderer::RunComputeShader(Shader::GetComputeShaderArray()[0], 2, pSRVs, nullptr, nullptr, 0, mpBufUAV, 1024, 1, 1);

}

void Gamemanger::Update() {


}

void Gamemanger::GameClear(bool win) {
		
	Application::GetScene()->SetSwitchFlag(true);

	if (win) {
		StaticManger::StateMap["GameClear"] = "true";
	}

	else if (!win) {
		StaticManger::StateMap["GameClear"] = "false";
	}
}


