/*
サウンドクラス
*/
#pragma once

// サウンド構造体
struct Sound
{
	IXAudio2SourceVoice* mSourceVoice;
	BYTE* mDataAudio;
	DWORD SizeAudio;
};

class AudioListener
{
private:

	// インスタンス
	static IXAudio2* mXaudio;
	static IXAudio2MasteringVoice* mMasteringVoice;

public:

	static void Init();
	static void Uninit();

	// プレイ
	static void Play(Sound* sound, int loop,float volume);
	// 停止(指定)
	static void Stop(Sound* sound);
	// 停止(全部)
	static void StopAll();

	// 音量設定
	static void SetVolume(float val) { 
		mMasteringVoice->SetVolume(val);
	};

	// Getter
	static bool Is_Playing(Sound* sound);
	static IXAudio2* GetXaudio() { return mXaudio; };


};