/*
�T�E���h�N���X
*/
#pragma once

// �T�E���h�\����
struct Sound
{
	IXAudio2SourceVoice* mSourceVoice;
	BYTE* mDataAudio;
	DWORD SizeAudio;
};

class AudioListener
{
private:

	// �C���X�^���X
	static IXAudio2* mXaudio;
	static IXAudio2MasteringVoice* mMasteringVoice;

public:

	static void Init();
	static void Uninit();

	// �v���C
	static void Play(Sound* sound, int loop,float volume);
	// ��~(�w��)
	static void Stop(Sound* sound);
	// ��~(�S��)
	static void StopAll();

	// ���ʐݒ�
	static void SetVolume(float val) { 
		mMasteringVoice->SetVolume(val);
	};

	// Getter
	static bool Is_Playing(Sound* sound);
	static IXAudio2* GetXaudio() { return mXaudio; };


};