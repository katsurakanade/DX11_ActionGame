#include "main.h"
#include "Renderer.h"
#include "Asset.h"
#include "Debug.h"
#include <thread>

std::vector<AssimpModel*> Asset::mAssimpModelList;
std::vector<ID3D11ShaderResourceView*> Asset::mTextureList;
std::vector<Sound*> Asset::mSoundList;

void Asset::LoadSceneAsset(){

	std::thread thread_loadmodel(LoadModel);
	std::thread thread_loadtexture(LoadTexture);
	std::thread thread_loadsound(LoadSound);

	thread_loadmodel.join();
	thread_loadtexture.join();
	thread_loadsound.join();

	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::SAMURAI);
	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::WIZARD);
	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::WARRIOR);
	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::ELF);
	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::STAR);
	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::SKY);

}

void Asset::UnloadSceneAsset() {

	for (AssimpModel* md : mAssimpModelList) {
		md->Unload();
	}

	for (ID3D11ShaderResourceView* tex : mTextureList) {
		tex->Release();
	}

	for (Sound* sound : mSoundList) {

		sound->mSourceVoice->Stop(0);

		sound->mSourceVoice->DestroyVoice();
		sound->mSourceVoice = nullptr;

		delete sound->mDataAudio;
		sound->mDataAudio = nullptr;
	}

}

void Asset::LoadModel() {

	auto start = std::chrono::system_clock::now();
	AddAssimpModelToList("asset\\model\\ball\\ball.obj");
	AddAssimpModelToList("asset\\model\\cube\\cube.obj");
	AddAssimpModelToList("asset\\model\\torus\\torus.obj");
	AddAssimpModelToList("asset\\model\\arrow\\arrow.obj");
	AddAssimpModelToList("asset\\model\\enemy\\enemy.obj");
	auto end = std::chrono::system_clock::now();

	Debug::OutputRuntime("Model Loaded", end, start);
}

void Asset::LoadTexture() {

	auto start = std::chrono::system_clock::now();
	AddTextureToList("asset/texture/number.png");
	AddTextureToList("asset/texture/Dirt.jpg");
	AddTextureToList("asset/texture/explosion.png");
	AddTextureToList("asset/texture/explosion2.png");
	AddTextureToList("asset/texture/Wizard.png");
	AddTextureToList("asset/texture/Samurai.png");
	AddTextureToList("asset/texture/Warrior.png");
	AddTextureToList("asset/texture/Elf.png");
	AddTextureToList("asset/texture/bar_empty.png");
	AddTextureToList("asset/texture/bar_fill.png");
	AddTextureToList("asset/texture/gameover.png");
	AddTextureToList("asset/texture/Clear.png");
	AddTextureToList("asset/texture/logo.png");
	AddTextureToList("asset/texture/white.png");
	AddTextureToList("asset/texture/star.jpg");
	AddTextureToList("asset/texture/sky.jpg");
	AddTextureToList("asset/texture/space_button.png");
	AddTextureToList("asset/texture/lightning.png");
	auto end = std::chrono::system_clock::now();
	Debug::OutputRuntime("Texture Loaded", end, start);
}

void Asset::LoadSound() {

	auto start = std::chrono::system_clock::now();
	AddSoundToList("asset/sound/bgm.wav");
	AddSoundToList("asset/sound/bgm2.wav");
	AddSoundToList("asset/sound/bgm3.wav");
	AddSoundToList("asset/sound/switch.wav");
	AddSoundToList("asset/sound/CollisionWall.wav");
	AddSoundToList("asset/sound/Explosion.wav");
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

