#pragma 

#include "AssimpModel.h"
#include "AudioListener.h"

enum class ASSIMP_MODEL_ENUM
{
	BALL,
	CUBE,
	TORUS,
	ARROW,
	ENEMY,
};

enum TEXTURE_ENUM {
	NUMBER,
	DIRT,
	EXP,
	EXP2,
	WIZARD,
	SAMURAI,
	WARRIOR,
	ELF,
	BAR_EMPTY,
	BAR_FILL,
	CLEAR,
	LOGO,
	WHITE,
	STAR,
	SKY,
	SPACEBUTTON,
	LIGHTNING,
};

enum class SOUND_ENUM {
	BGM_01,
	BGM_02,
	BGM_03,
	SE_01,
	SE_02,
	SE_03,
};

class Asset
{

private:

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

protected:

	static std::vector<AssimpModel*> mAssimpModelList;
	static std::vector<ID3D11ShaderResourceView*> mTextureList;
	static std::vector<Sound*> mSoundList;

	static void AddAssimpModelToList(const char* value) {

		AssimpModel* md = new AssimpModel();
		md->Load(value);
		mAssimpModelList.emplace_back(md);
	}

	static void AddTextureToList(const char* value) {
		ID3D11ShaderResourceView* tex;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),value,NULL,NULL,&tex,NULL);
		mTextureList.emplace_back(tex);
	}

	static void AddSoundToList(const char* value) {

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

public:

	static void LoadSceneAsset();
	static void UnloadSceneAsset();
	
	static AssimpModel* GetAssimpModel(ASSIMP_MODEL_ENUM index) { return mAssimpModelList[(int)index]; };
	static ID3D11ShaderResourceView* GetTexture(int index) { return mTextureList[index]; };
	static Sound* GetSound(SOUND_ENUM index) { return mSoundList[(int)index]; };

	static std::vector<Sound*> GetSoundList(){ return mSoundList; };
};

