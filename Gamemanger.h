#pragma once

#include "Resource.h"
#include "Level.h"

struct BufType
{
	int     s32;
};

enum class RoundState{
	PLAYER_ROUND,
	ENEMY_ROUND,
};


class Gamemanger : public Resource
{

private:

	bool mGameClear = false;

	int mRound;

	Level* mpLevel;

	void GameClear(bool win);



public:

	RoundState mState;

	// Compute Test
	BufType mBuf_0[16];
	BufType mBuf_1[16];
	ID3D11Buffer* mpBuf_0 = nullptr;
	ID3D11Buffer* mpBuf_1 = nullptr;
	ID3D11Buffer* mpBufResult = nullptr;
	ID3D11ShaderResourceView* mpBufSRV0 = nullptr;
	ID3D11ShaderResourceView* mpBufSRV1 = nullptr;
	ID3D11UnorderedAccessView* mpBufUAV = nullptr;

	void Init();
	void Unint() {};
	void Update();
	void Render() {};

};

