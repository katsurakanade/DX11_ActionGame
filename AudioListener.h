#pragma once

struct Sound
{
	IXAudio2SourceVoice* mSourceVoice;
	BYTE* mDataAudio;
	DWORD SizeAudio;
};

class AudioListener
{
private:

	static IXAudio2* mXaudio;
	static IXAudio2MasteringVoice* mMasteringVoice;

public:

	static void Init();
	static void Unint();

	static void Play(Sound* sound,bool loop);
	static void Stop(Sound* sound);
	static void StopAll();

	static void SetVolume(float val) { 
		mMasteringVoice->SetVolume(val); 
	};

	static IXAudio2* GetXaudio() { return mXaudio; };
};

