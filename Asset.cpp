#include "main.h"
#include "Renderer.h"
#include "Asset.h"
#include "Debug.h"
#include <thread>
#include "Lib/nlohmann/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

void Asset::LoadSceneAsset(){

	// JSONデータ完全性チェック
	CheckJSONDataIntegrity();

	// アセットロード(マルチスレッド)
	std::thread thread_loadmodel(&Asset::LoadModel,this);
	std::thread thread_loadanimation(&Asset::LoadAnimation, this);
	std::thread thread_loadtexture(&Asset::LoadTexture, this);
	std::thread thread_loadsound(&Asset::LoadSound, this);
	thread_loadmodel.join();
	thread_loadanimation.join();
	thread_loadtexture.join();
	thread_loadsound.join();
	

	// アセットファイル完全性チェック
	if (mLostFileList.size() > 0) {
		std::string str;
		for (int i = 0; i < mLostFileList.size(); i++) {
			str += mLostFileList[i].c_str();
			str += "\n";
		}
		MessageBox(GetWindow(), str.c_str(), "アセットファイル読み込みエラー", MB_OK);
		if (MessageBox(GetWindow(), "アセットファイル読み込みエラー", "エラー", MB_OK)) {
			exit(1);
		}
	}
	mLostFileList.clear();

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
		if (tex != nullptr) {
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

	std::string jsonpath;
	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		jsonpath = "asset\\json_asset\\Asset_Model_Title.json";
		break;
	case SCENE_ASSET::GAME:
		jsonpath = "asset\\json_asset\\Asset_Model_Game.json";
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

	std::vector <std::string> path = GetPathFromFile(jsonpath.c_str());

	// シーンことロード
	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		for (unsigned int i = 0; i < path.size(); i++) {
			AddAssimpModelToList(path[i].c_str());
		}
		break;
	case SCENE_ASSET::GAME:
		for (unsigned int i = 0; i < path.size() - 3; i++) {
			AddAssimpModelToList(path[i].c_str());
		}
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

	auto end = std::chrono::system_clock::now();

	Debug::OutputRuntime("Model Loaded", end, start);
}

void Asset::LoadAnimation() {

	std::string jsonpath_model;
	std::string jsonpath_animation;
	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		jsonpath_model = "asset\\json_asset\\Asset_Model_Title.json";
		break;
	case SCENE_ASSET::GAME:
		jsonpath_model = "asset\\json_asset\\Asset_Model_Game.json";
		jsonpath_animation = "asset\\json_asset\\Asset_Animation_Game.json";
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

	std::vector <std::string> index_animation;
	std::vector <std::string> path = GetPathFromFile(jsonpath_model.c_str());
	std::vector <std::string> animationpath = GetPathFromFile(jsonpath_animation.c_str());

	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		break;
	case SCENE_ASSET::GAME:

		index_animation.push_back("Idle");
		index_animation.push_back("Running");
		index_animation.push_back("Attack");
		index_animation.push_back("Mage");

		for (unsigned int i = 6; i < path.size(); i++) {
			AddAssimpModelToList(path[i].c_str(), animationpath, index_animation);
		}

		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}
}

void Asset::LoadTexture() {

	auto start = std::chrono::system_clock::now();

	std::string jsonpath;
	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		jsonpath = "asset\\json_asset\\Asset_Texture_Title.json";
		break;
	case SCENE_ASSET::GAME:
		jsonpath = "asset\\json_asset\\Asset_Texture_Game.json";
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

	std::vector <std::string> path = GetPathFromFile(jsonpath.c_str());

	// シーン別ロード
	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		for (unsigned int i = 0; i < path.size(); i++) {
			AddTextureToList(path[i].c_str());
		}
		break;
	case SCENE_ASSET::GAME:
		for (unsigned int i = 0; i < path.size() ; i++) {
			AddTextureToList(path[i].c_str());
		} 
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

	std::string jsonpath;
	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		jsonpath = "asset\\json_asset\\Asset_Sound_Title.json";
		break;
	case SCENE_ASSET::GAME:
		jsonpath = "asset\\json_asset\\Asset_Sound_Game.json";
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

	std::vector <std::string> path = GetPathFromFile(jsonpath.c_str());

	// シーンことロード
	switch (mScene)
	{
	case SCENE_ASSET::TITLE:
		for (unsigned int i = 0; i < path.size(); i++) {
			AddSoundToList(path[i].c_str());
		}
		break;
	case SCENE_ASSET::GAME:
		for (unsigned int i = 0; i < path.size(); i++) {
			AddSoundToList(path[i].c_str());
		}
		break;
	case SCENE_ASSET::RESULT:
		break;
	default:
		break;
	}

	auto end = std::chrono::system_clock::now();

	Debug::OutputRuntime("Sound Loaded", end, start);
}

void Asset::CheckFile(const char* path) {

	auto checkfile = [](const char* path) ->bool {std::ifstream file; file.open(path); return file.is_open(); };
	if (!checkfile(path)) 
		mLostFileList.push_back(path);
}

void Asset::CheckJSONDataIntegrity() {

	int error = 0;

	CheckFile("asset\\json_asset\\Asset_Model_Game.json");
	CheckFile("asset\\json_asset\\Asset_Animation_Game.json");
	CheckFile("asset\\json_asset\\Asset_Model_Title.json");
	CheckFile("asset\\json_asset\\Asset_Texture_Game.json");
	CheckFile("asset\\json_asset\\Asset_Texture_Title.json");
	CheckFile("asset\\json_scene_object\\grass.json");
	CheckFile("asset\\json_scene_object\\props.json");
	CheckFile("asset\\json_particle\\PlayerAttack_FireBall_Particle.json");
	CheckFile("asset\\json_particle\\PlayerAttack_Simple_Particle.json");
	CheckFile("asset\\json_particle\\PlayerSwitchCharacter_Particle.json");
	CheckFile("asset\\json_particle\\Title_Particle.json");

	if (mLostFileList.size() > 0) {
		std::string str;
		for (int i = 0; i < mLostFileList.size(); i++) {
			str += mLostFileList[i].c_str();
			str += "\n";
		}
		MessageBox(GetWindow(), str.c_str(), "JSONファイル読み込みエラー", MB_OK);
		if (MessageBox(GetWindow(), "JSONファイル読み込みエラー", "エラー", MB_OK)) {
			exit(1);
		}
	}

	mLostFileList.clear();
}

std::vector <std::string> Asset::GetPathFromFile(const char* file) {

	std::vector <std::string> result;

	std::string filename = file;
	std::ifstream fp;
	int length;

	fp.open(filename);

	if (fp.is_open()) {
		fp >> length;

		// サイズ <= 0
		if (length <= 0) {
			return result;
		}

		for (int i = 0; i < length; i++) {
			json data;
			fp >> data;
			result.push_back(data["Path"]); 
		}

	}

	return result;
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



