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
	HUMAN,
	KNIGHT
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
	GAMEOVER,
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
	SE_04,
};

class Asset
{

private:

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

protected:

	std::vector<AssimpModel*> mAssimpModelList;
	std::vector<ID3D11ShaderResourceView*> mTextureList;
	std::vector<Sound*> mSoundList;

	void AddAssimpModelToList(const char* value) {

		AssimpModel* md = new AssimpModel();
		md->Load(value);
		mAssimpModelList.push_back(md);
	}

	void AddTextureToList(const char* value) {
		ID3D11ShaderResourceView* tex;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),value,NULL,NULL,&tex,NULL);
		mTextureList.push_back(tex);
	}

	void AddSoundToList(const char* value) {

		Sound* sound = new Sound();

		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(value, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);

		ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);

		CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);

		ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);


		//// オーディオデータ読み込み
		CheckChunk(hFile, 'atad', &sound->SizeAudio, &dwChunkPosition);
		sound->mDataAudio = (BYTE*)malloc(sound->SizeAudio);
		ReadChunkData(hFile, sound->mDataAudio, sound->SizeAudio, dwChunkPosition);

		// ソースボイスの生成
		AudioListener::GetXaudio()->CreateSourceVoice(&sound->mSourceVoice, &(wfx.Format));

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = sound->SizeAudio;
		buffer.pAudioData = sound->mDataAudio;
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = -1;

		// オーディオバッファの登録
		sound->mSourceVoice->SubmitSourceBuffer(&buffer);

		mSoundList.emplace_back(sound);
	}

	void LoadModel();
	void LoadTexture();
	void LoadSound();

public:

	void LoadSceneAsset();
	void UnloadSceneAsset();
	
	AssimpModel* GetAssimpModel(ASSIMP_MODEL_ENUM index) { return mAssimpModelList[(int)index]; };
	ID3D11ShaderResourceView* GetTexture(int index) { return mTextureList[index]; };
	Sound* GetSound(SOUND_ENUM index) { return mSoundList[(int)index]; };

	std::vector<Sound*> GetSoundList(){ return mSoundList; };
};

