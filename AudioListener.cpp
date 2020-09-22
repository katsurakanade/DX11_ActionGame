#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "AudioListener.h"

IXAudio2* AudioListener::mXaudio;
IXAudio2MasteringVoice* AudioListener::mMasteringVoice;

void AudioListener::Init() {

	// COM������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio����
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

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = sound->SizeAudio;
	buffer.pAudioData = sound->mDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = loop;

	// ��Ԏ擾
	sound->mSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{
		// �ꎞ��~
		sound->mSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		sound->mSourceVoice->FlushSourceBuffers();

	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	sound->mSourceVoice->SubmitSourceBuffer(&buffer);

	sound->mSourceVoice->SetVolume(volume);

	// �Đ�
	sound->mSourceVoice->Start(0);
}

void AudioListener::Stop(Sound* sound){
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	sound->mSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{
		// �ꎞ��~
		sound->mSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
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