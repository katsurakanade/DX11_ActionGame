/*
�A�Z�b�g�N���X
*/

#pragma once

#include "AssimpModel.h"
#include "AudioListener.h"

// �V�[��
enum class SCENE_ASSET {
	TITLE,GAME,RESULT
};
// �^�C�g��_���f��
enum class ASSIMP_MODEL_ENUM_TITLE
{
	BALL,
};
// �^�C�g��_�e�N�X�`��
enum class TEXTURE_ENUM_TITLE {
	LOGO,
	WHITE,
	SKY,
	STAR,
	SPACEBUTTON,
};
// �^�C�g��_�T�E���h
enum class SOUND_ENUM_TITLE {
	BGM_01,
	SE_01,
};
// �Q�[��_���f��
enum class ASSIMP_MODEL_ENUM_GAME
{
	BALL,
	CUBE,
	ENEMY,
	HUMAN,
	HUMAN2,
	TORUS,
	SWORD,
	ROCK,
};
// �Q�[��_�e�N�X�`��
enum class TEXTURE_ENUM_GAME
{
	WHITE,
	SKY,
	STAR,
	BAR_EMPTY,
	BAR_FILL,
	EXPLOSION,
	PARTICLE,
	GRASS,
	FRAME,
	ROUND_FRAME,
	SWORD_ICON,
	PLANT,
	DIRT,
	HAL,
	STONE,
	FOG,
	HANE,
};
// �Q�[��_�T�E���h
enum class SOUND_ENUM_GAME {
	BGM_02,
};

class Asset
{

private:

	// �T�E���h�p
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	// �V�[��
	SCENE_ASSET mScene;

protected:

	// ���f��
	std::vector<AssimpModel*> mAssimpModelList;
	// �e�N�X�`��
	std::vector<ID3D11ShaderResourceView*> mTextureList;
	// �T�E���h
	std::vector<Sound*> mSoundList;

	// ���f���ǉ�
	void AddAssimpModelToList(const char* value) {
		AssimpModel* md = new AssimpModel(false);
		md->Load(value);
		mAssimpModelList.push_back(md);
	}
	// ���f���ǉ�(�A�j���[�V��������)
	void AddAssimpModelToList(const char* value, std::vector<std::string> animationpass , std::vector<std::string> animationname) {
		AssimpModel* md = new AssimpModel(true);
		md->Load(value);

		for (unsigned int i = 0; i < animationpass.size(); i++) {
			md->LoadAnimation(animationpass[i],animationname[i]);
		}

		mAssimpModelList.push_back(md);
	}
	// �e�N�X�`���ǉ�
	void AddTextureToList(const char* value) {
		ID3D11ShaderResourceView* tex;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),value,NULL,NULL,&tex,NULL);
		mTextureList.push_back(tex);
	}
	// �T�E���h�ǉ�
	void AddSoundToList(const char* value) {

		Sound* sound = new Sound();

		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(value, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);

		ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);

		CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);

		ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);


		//// �I�[�f�B�I�f�[�^�ǂݍ���
		CheckChunk(hFile, 'atad', &sound->SizeAudio, &dwChunkPosition);
		sound->mDataAudio = (BYTE*)malloc(sound->SizeAudio);
		ReadChunkData(hFile, sound->mDataAudio, sound->SizeAudio, dwChunkPosition);

		// �\�[�X�{�C�X�̐���
		AudioListener::GetXaudio()->CreateSourceVoice(&sound->mSourceVoice, &(wfx.Format));

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = sound->SizeAudio;
		buffer.pAudioData = sound->mDataAudio;
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = -1;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		sound->mSourceVoice->SubmitSourceBuffer(&buffer);

		mSoundList.emplace_back(sound);
	}

	// ���[�h
	void LoadModel();
	void LoadTexture();
	void LoadSound();

public:

	Asset() = delete;
	Asset(SCENE_ASSET scene) : mScene(scene) {};

	// ���[�h�V�[���A�Z�b�g
	void LoadSceneAsset();
	// �A�����[�h�V�[���A�Z�b�g
	void UnloadSceneAsset();
	
	// Getter
	SCENE_ASSET GetScene() { return mScene; };
	AssimpModel* GetAssimpModel(int index) { return mAssimpModelList[(int)index]; };
	ID3D11ShaderResourceView* GetTexture(int index) { return mTextureList[index]; };
	Sound* GetSound(int index) { return mSoundList[(int)index]; };
	std::vector<Sound*> GetSoundList(){ return mSoundList; };
};

