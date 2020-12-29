/*
�A�Z�b�g�N���X
*/

#pragma once

#include "AssimpModel.h"
#include "AudioListener.h"
#include "FileManger.h"

// �V�[��
enum class SCENE_ASSET {
	TITLE,GAME,RESULT
};
// �^�C�g��_���f��
enum class ASSIMP_MODEL_ENUM_TITLE
{
	BALL,END
};
// �^�C�g��_�e�N�X�`��
enum class TEXTURE_ENUM_TITLE {
	WHITE,
	SKY,
	STAR,
	SPACEBUTTON,
	TITLE,
	PARTICLE,
	END,
};
// �^�C�g��_�T�E���h
enum class SOUND_ENUM_TITLE {
	BGM_01,
	SE_01,
	END,
};
// �Q�[��_���f��
enum class ASSIMP_MODEL_ENUM_GAME
{
	BALL,
	CUBE,
	TORUS,
	SWORD,
	ROCK,
	WALL,
	ENEMY,
	BOSS,
	HUMAN,
	HUMAN2,
	END,
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
	FRAME,
	ROUND_FRAME,
	PLANT,
	DIRT,
	DIRT_NORMAL,
	DIRT_HEIGHT,
	FOG,
	HANE,
	CHARACTERICON_0,
	CHARACTERICON_1,
	NUMBER,
	END,
};
// �Q�[��_�T�E���h
enum class SOUND_ENUM_GAME {
	BGM_02,
	END,
};

class Asset
{

private:

	// �T�E���h�p
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	// �V�[��
	SCENE_ASSET mScene;
	// �t�@�C���p�X�擾
	std::vector <std::string> GetPathFromFile(const char* file);

protected:

	// ���f��
	std::vector<AssimpModel*> mAssimpModelList;
	// �e�N�X�`��
	std::vector<ID3D11ShaderResourceView*> mTextureList;
	// �T�E���h
	std::vector<Sound*> mSoundList;
	// ���݂��Ă��Ȃ��t�@�C������
	std::vector<std::string> mLostFileList;

	// ���f���ǉ�
	void AddAssimpModelToList(const char* value) {
		AssimpModel* md = new AssimpModel(false);
		if (md->Load(value))
			mAssimpModelList.push_back(md);
		else
			mLostFileList.push_back(value);
		
	}
	// ���f���ǉ�(�A�j���[�V��������)
	void AddAssimpModelToList(const char* value, std::vector<std::string> animationpass , std::vector<std::string> animationname) {
		AssimpModel* md = new AssimpModel(true);
		if (md->Load(value)) {
			for (unsigned int i = 0; i < animationpass.size(); i++) {
				if (md->LoadAnimation(animationpass[i], animationname[i])) {

				}
				else {
					mLostFileList.push_back(animationpass[i]);
				}
			}
			mAssimpModelList.push_back(md);
		}
		else
			mLostFileList.push_back(value);
	}
	// �e�N�X�`���ǉ�
	void AddTextureToList(const char* value) {

		ID3D11ShaderResourceView* tex = nullptr;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),value,NULL,NULL,&tex,NULL);
		if (tex)
			mTextureList.push_back(tex);
		else
			mLostFileList.push_back(value);
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

		if (CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition) != S_OK) {
			mLostFileList.push_back(value);
			return;
		}
		else if (ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition) != S_OK) {
			mLostFileList.push_back(value);
			return;
		}
		else if (CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition) != S_OK) {
			mLostFileList.push_back(value);
			return;
		}
		else if (ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition) != S_OK) {
			mLostFileList.push_back(value);
			return;
		}

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
	void LoadAnimation();
	void LoadTexture();
	void LoadSound();

	// �t�@�C���`�F�b�N
	void CheckFile(const char* path);

	// JSON�f�[�^���S���`�F�b�N
	void CheckJSONDataIntegrity();

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

