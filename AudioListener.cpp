#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "AudioListener.h"

IXAudio2* AudioListener::mXaudio;
IXAudio2MasteringVoice* AudioListener::mMasteringVoice;

void AudioListener::Init() {

	// COM初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio生成
	XAudio2Create(&mXaudio, 0);

	mXaudio->CreateMasteringVoice(&mMasteringVoice);
}

void AudioListener::Uninit() {

	if (mMasteringVoice) {
		mMasteringVoice->DestroyVoice();
	}

	if (mXaudio) {
		mXaudio->Release();
	}

	CoUninitialize();

}

void AudioListener::Play(Sound* sound,int loop, float volume) {

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = sound->SizeAudio;
	buffer.pAudioData = sound->mDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = loop;

	// 状態取得
	sound->mSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{
		// 一時停止
		sound->mSourceVoice->Stop(0);

		// オーディオバッファの削除
		sound->mSourceVoice->FlushSourceBuffers();

	}

	// オーディオバッファの登録
	sound->mSourceVoice->SubmitSourceBuffer(&buffer);

	sound->mSourceVoice->SetVolume(volume);

	// 再生
	sound->mSourceVoice->Start(0);
}

void AudioListener::Stop(Sound* sound){
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	sound->mSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{
		// 一時停止
		sound->mSourceVoice->Stop(0);

		// オーディオバッファの削除
		sound->mSourceVoice->FlushSourceBuffers();
	}
}

void AudioListener::StopAll() {

	for (Sound* s : Application::GetAsset()->GetSoundList()) {

		if (s->mSourceVoice)
		{
			s->mSourceVoice->Stop(0);
		}
	}
}

bool AudioListener::Is_Playing(Sound* sound) {

	XAUDIO2_VOICE_STATE xa2state;

	sound->mSourceVoice->GetState(&xa2state);

	return xa2state.BuffersQueued;
}