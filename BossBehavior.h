/*
ボス行為クラス
*/
#pragma once

#include "EnemyBehavior.h"

enum class BEHAVIOR_STATE_BOSS {
	Idle, // 待機
	Chase, // 追跡
	Attack, // 攻撃
	Magic, // 魔法
	Summon, // 召喚
	Dying, // 死亡
};

class BossBehavior : public EnemyBehavior
{

private:

	// ステートマップ
	std::map <BEHAVIOR_STATE_BOSS, std::string> mStatemap;
	// スタート
	bool mStart;
	
	// 召喚関連 -----------------------------
	// 召喚した
	bool mUsedSummon;
	// 召喚用スレッド
	std::thread mSummonThread;
	// 待ち時間
	float mSummonThreadWaitTime;
	// 召喚
	void Summon();
	// 召喚更新処理
	void Summonprocess();
	// 召喚した敵のポインタ
	Enemy* mSummonenemy;
	// 召喚予備敵の座標
	D3DXVECTOR3 mSummonenemyPos;
	// 召喚魔法陣エフェクト
	Sprite* mSummonSprite;
	// -------------------------------------

	// 魔法攻撃関連 ----------------------
	float mSpellTimeMagic;
	bool mUsedMagic;
	// -------------------------------------

	float mCoolSkill;

	// スキル使え可能
	bool mCanUseSkill;
	// 死亡
	bool mDead;

protected:

	// 行動決め
	void ChooseAction();
	// 行動実行
	void RunAction();

public:

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();
	void DataPanel();


};

