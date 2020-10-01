#include "main.h"
#include "Renderer.h"
#include "Asset.h"
#include "Debug.h"
#include <thread>

void Asset::LoadSceneAsset(){

	std::thread thread_loadmodel(&Asset::LoadModel,this);
	std::thread thread_loadtexture(&Asset::LoadTexture, this);
	std::thread thread_loadsound(&Asset::LoadSound, this);

	thread_loadmodel.join();
	thread_loadtexture.join();
	thread_loadsound.join();

	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		mAssimpModelList[(int)ASSIMP_MODEL_ENUM_TITLE::BALL]->PushTextureSelect(this,(int)TEXTURE_ENUM_TITLE::STAR);
		mAssimpModelList[(int)ASSIMP_MODEL_ENUM_TITLE::BALL]->PushTextureSelect(this, (int)TEXTURE_ENUM_TITLE::SKY);
		break;
	case SCENE_ASSET::GAME:
		mAssimpModelList[(int)ASSIMP_MODEL_ENUM_GAME::BALL]->PushTextureSelect(this, (int)TEXTURE_ENUM_GAME::WHITE);
		mAssimpModelList[(int)ASSIMP_MODEL_ENUM_GAME::BALL]->PushTextureSelect(this, (int)TEXTURE_ENUM_GAME::SKY);
		mAssimpModelList[(int)ASSIMP_MODEL_ENUM_GAME::BALL]->PushTextureSelect(this, (int)TEXTURE_ENUM_GAME::STAR);
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

}

void Asset::UnloadSceneAsset() {

	for (AssimpModel* md : mAssimpModelList) {
		if (md) {
			md->Unload();
			delete md;
			md = nullptr;
		}
	}

	for (ID3D11ShaderResourceView* tex : mTextureList) {
		if (tex) {
			tex->Release();
		}
	}

	for (Sound* sound : mSoundList) {

		sound->mSourceVoice->Stop(0);

		sound->mSourceVoice->DestroyVoice();
		sound->mSourceVoice = nullptr;

		delete sound->mDataAudio;
		sound->mDataAudio = nullptr;
	}

	std::vector<AssimpModel*>().swap(mAssimpModelList);
	std::vector<ID3D11ShaderResourceView*>().swap(mTextureList);
	std::vector<Sound*>().swap(mSoundList);

}

void Asset::LoadModel() {

	auto start = std::chrono::system_clock::now();

	std::vector <std::string> animation;
	std::vector <std::string> pass;

	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		AddAssimpModelToList("asset\\model\\ball\\ball.obj");
		break;
	case SCENE_ASSET::GAME:

		AddAssimpModelToList("asset\\model\\ball\\ball.obj");
		AddAssimpModelToList("asset\\model\\cube\\cube.obj");

		pass.push_back("asset\\model\\human\\Idle.fbx");
		pass.push_back("asset\\model\\human\\Running.fbx");
		pass.push_back("asset\\model\\human\\Jump.fbx");
		pass.push_back("asset\\model\\human\\Roll.fbx");
		pass.push_back("asset\\model\\human\\Attack.fbx");
		animation.push_back("Idle");
		animation.push_back("Running");
		animation.push_back("Jump");
		animation.push_back("Roll");
		animation.push_back("Attack");

		AddAssimpModelToList("asset\\model\\enemy\\Enemy.fbx", pass, animation);
		AddAssimpModelToList("asset\\model\\human\\Human.fbx",pass, animation);
		AddAssimpModelToList("asset\\model\\torus\\torus.obj");
		AddAssimpModelToList("asset\\model\\sword\\sword.obj");

		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

	auto end = std::chrono::system_clock::now();

	Debug::OutputRuntime("Model Loaded", end, start);
}

void Asset::LoadTexture() {

	auto start = std::chrono::system_clock::now();

	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		AddTextureToList("asset/texture/logo.png");
		AddTextureToList("asset/texture/white.png");
		AddTextureToList("asset/texture/star.jpg");
		AddTextureToList("asset/texture/sky.jpg");
		AddTextureToList("asset/texture/space_button.png");
		break;
	case SCENE_ASSET::GAME:
		AddTextureToList("asset/texture/white.png");
		AddTextureToList("asset/texture/sky.jpg");
		AddTextureToList("asset/texture/star.jpg");
		AddTextureToList("asset/texture/Hp_frame.png");
		AddTextureToList("asset/texture/Hp_line.png");
		AddTextureToList("asset/texture/explosion.png");
		AddTextureToList("asset/texture/Particle.png");
		AddTextureToList("asset/texture/Grass.jpg");
		AddTextureToList("asset/texture/Frame.png");
		AddTextureToList("asset/texture/RoundFrame.png");
		AddTextureToList("asset/texture/Sword_Icon.png");
		AddTextureToList("asset/texture/Plant.png");
		AddTextureToList("asset/texture/Dirt.jpg");
		AddTextureToList("asset/texture/hal.png");
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

	auto end = std::chrono::system_clock::now();
	Debug::OutputRuntime("Texture Loaded", end, start);
}

void Asset::LoadSound() {

	auto start = std::chrono::system_clock::now();


	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		AddSoundToList("asset/sound/bgm.wav");
		AddSoundToList("asset/sound/switch.wav");
		break;
	case SCENE_ASSET::GAME:
		AddSoundToList("asset/sound/bgm2.wav");
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}
	/*AddSoundToList("asset/sound/bgm.wav");
	AddSoundToList("asset/sound/bgm2.wav");
	AddSoundToList("asset/sound/bgm3.wav");
	AddSoundToList("asset/sound/switch.wav");
	AddSoundToList("asset/sound/CollisionWall.wav");
	AddSoundToList("asset/sound/Explosion.wav");
	AddSoundToList("asset/sound/razer.wav");*/
	auto end = std::chrono::system_clock::now();

	Debug::OutputRuntime("Sound Loaded", end, start);
}

HRESULT Asset::CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

HRESULT Asset::ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

