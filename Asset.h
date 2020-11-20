/*
アセットクラス
*/

#pragma once

#include "AssimpModel.h"
#include "AudioListener.h"
#include "FileManger.h"

// シーン
enum class SCENE_ASSET {
	TITLE,GAME,RESULT
};
// タイトル_モデル
enum class ASSIMP_MODEL_ENUM_TITLE
{
	BALL,
};
// タイトル_テクスチャ
enum class TEXTURE_ENUM_TITLE {
	WHITE,
	SKY,
	STAR,
	SPACEBUTTON,
	TITLE,
	PARTICLE,
};
// タイトル_サウンド
enum class SOUND_ENUM_TITLE {
	BGM_01,
	SE_01,
};
// ゲーム_モデル
enum class ASSIMP_MODEL_ENUM_GAME
{
	BALL,
	CUBE,
	TORUS,
	SWORD,
	ROCK,
	WALL,
	ENEMY,
	HUMAN,
	HUMAN2,
};
// ゲーム_テクスチャ
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
	DIRT_NORMAL,
	DIRT_HEIGHT,
	HAL,
	FOG,
	HANE,
	CHARACTERICON_0,
	CHARACTERICON_1,
	BAG,
	NUMBER,
};
// ゲーム_サウンド
enum class SOUND_ENUM_GAME {
	BGM_02,
};

class Asset
{

private:

	// サウンド用
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	// シーン
	SCENE_ASSET mScene;
	// ファイルパス取得
	std::vector <std::string> GetPathFromFile(const char* file);

protected:

	// モデル
	std::vector<AssimpModel*> mAssimpModelList;
	// テクスチャ
	std::vector<ID3D11ShaderResourceView*> mTextureList;
	// サウンド
	std::vector<Sound*> mSoundList;

	// モデル追加
	void AddAssimpModelToList(const char* value) {
		AssimpModel* md = new AssimpModel(false);
		md->Load(value);
		mAssimpModelList.push_back(md);
	}
	// モデル追加(アニメーションあり)
	void AddAssimpModelToList(const char* value, std::vector<std::string> animationpass , std::vector<std::string> animationname) {
		AssimpModel* md = new AssimpModel(true);
		md->Load(value);

		for (unsigned int i = 0; i < animationpass.size(); i++) {
			md->LoadAnimation(animationpass[i],animationname[i]);
		}

		mAssimpModelList.push_back(md);
	}
	// テクスチャ追加
	void AddTextureToList(const char* value) {

		ID3D11ShaderResourceView* tex = nullptr;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),value,NULL,NULL,&tex,NULL);
		if (!tex) {
			MessageBox(GetWindow(), value, "Error", MB_OK);
		}
		assert(tex);

		mTextureList.push_back(tex);
	}
	// サウンド追加
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

	// ロード
	void LoadModel();
	void LoadTexture();
	void LoadSound();

public:

	Asset() = delete;
	Asset(SCENE_ASSET scene) : mScene(scene) {};

	// ロードシーンアセット
	void LoadSceneAsset();
	// アンロードシーンアセット
	void UnloadSceneAsset();
	
	// Getter
	SCENE_ASSET GetScene() { return mScene; };
	AssimpModel* GetAssimpModel(int index) { return mAssimpModelList[(int)index]; };
	ID3D11ShaderResourceView* GetTexture(int index) { return mTextureList[index]; };
	Sound* GetSound(int index) { return mSoundList[(int)index]; };
	std::vector<Sound*> GetSoundList(){ return mSoundList; };
};

