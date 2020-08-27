#include "main.h"
#include "Renderer.h"
#include "Asset.h"
#include "AudioListener.h"

IXAudio2* AudioListener::mXaudio;
IXAudio2MasteringVoice* AudioListener::mMasteringVoice;

void AudioListener::Init() {

	// COM������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio����
	XAudio2Create(&mXaudio, 0);

	// �}�X�^�����O�{�C�X����
	mXaudio->CreateMasteringVoice(&mMasteringVoice);
}

void AudioListener::Unint() {

	mMasteringVoice->DestroyVoice();

	mXaudio->Release();

	CoUninitialize();

}

void AudioListener::Play(Sound* sound,bool loop) {

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

	for (Sound* s : Asset::GetSoundList()) {

		if (s->mSourceVoice)
		{
			s->mSourceVoice->Stop(0);
		}
	}
}