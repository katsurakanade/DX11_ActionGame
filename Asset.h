#pragma 

#include "AssimpModel.h"
#include "AudioListener.h"

enum class SCENE_ASSET {
	TITLE,GAME,RESULT
};

enum class ASSIMP_MODEL_ENUM
{
	BALL,
	CUBE,
	TORUS,
	ARROW,
	ENEMY,
	HUMAN,
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
	//LOGO,
	//WHITE,
	//STAR,
	//SKY,
	//SPACEBUTTON,
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

enum class ASSIMP_MODEL_ENUM_TITLE
{
	BALL,
};

enum class TEXTURE_ENUM_TITLE {
	LOGO,
	WHITE,
	SKY,
	STAR,
	SPACEBUTTON,
};

enum class SOUND_ENUM_TITLE {
	BGM_01,
	SE_01,
};

enum class ASSIMP_MODEL_ENUM_GAME
{
	BALL,
	CUBE,
	ENEMY,
	HUMAN,
};

enum class TEXTURE_ENUM_GAME {
	WHITE,
	SKY,
	STAR,
	BAR_EMPTY,
	BAR_FILL,
	EXPLOSION,
	PARTICLE,
};

enum class SOUND_ENUM_GAME {
	BGM_02,
};

class Asset
{

private:

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	SCENE_ASSET mScene;

protected:

	std::vector<AssimpModel*> mAssimpModelList;
	std::vector<ID3D11ShaderResourceView*> mTextureList;
	std::vector<Sound*> mSoundList;

	void AddAssimpModelToList(const char* value) {
		AssimpModel* md = new AssimpModel(false);
		md->Load(value);
		mAssimpModelList.push_back(md);
	}

	void AddAssimpModelToList(const char* value, std::vector<std::string> animationpass , std::vector<std::string> animationname) {
		AssimpModel* md = new AssimpModel(true);
		md->Load(value);

		for (int i = 0; i < animationpass.size(); i++) {
			md->LoadAnimation(animationpass[i],animationname[i]);
		}

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

	Asset() = delete;
	Asset(SCENE_ASSET scene) : mScene(scene) {};

	void LoadSceneAsset();
	void UnloadSceneAsset();
	
	SCENE_ASSET GetScene() { return mScene; };

	AssimpModel* GetAssimpModel(int index) { return mAssimpModelList[(int)index]; };
	ID3D11ShaderResourceView* GetTexture(int index) { return mTextureList[index]; };
	Sound* GetSound(int index) { return mSoundList[(int)index]; };

	std::vector<Sound*> GetSoundList(){ return mSoundList; };
};

