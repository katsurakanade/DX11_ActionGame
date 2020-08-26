#include "main.h"
#include "Renderer.h"
#include "Asset.h"
#include "Debug.h"

std::vector<AssimpModel*> Asset::mAssimpModelList;
std::vector<ID3D11ShaderResourceView*> Asset::mTextureList;

void Asset::LoadSceneAsset(){

	const auto start = std::chrono::system_clock::now();

	AddAssimpModelToList("asset\\model\\ball\\ball.obj");
	AddAssimpModelToList("asset\\model\\cube\\cube.obj");
	AddAssimpModelToList("asset\\model\\torus\\torus.obj");
	AddAssimpModelToList("asset\\model\\arrow\\arrow.obj");
	AddAssimpModelToList("asset\\model\\enemy\\enemy.obj");

	AddTextureToList("asset/texture/number.png");
	AddTextureToList("asset/texture/Dirt.jpg");
	AddTextureToList("asset/texture/explosion2.png");
	AddTextureToList("asset/texture/Wizard.png");
	AddTextureToList("asset/texture/Samurai.png");
	AddTextureToList("asset/texture/Warrior.png");
	AddTextureToList("asset/texture/Elf.png");
	AddTextureToList("asset/texture/bar_empty.png");
	AddTextureToList("asset/texture/bar_fill.png");
	AddTextureToList("asset/texture/Clear.png");
	AddTextureToList("asset/texture/logo.png");
	AddTextureToList("asset/texture/white.png");

	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::SAMURAI);
	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::WIZARD);
	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::WARRIOR);
	mAssimpModelList[(int)ASSIMP_MODEL_ENUM::BALL]->PushTextureSelect((int)TEXTURE_ENUM::ELF);

	const auto end = std::chrono::system_clock::now();

	Debug::OutputRuntime("Asset Loaded",end, start);
}

void Asset::UnloadSceneAsset() {

	for (AssimpModel* md : mAssimpModelList) {
		md->Unload();
	}

	for (ID3D11ShaderResourceView* tex : mTextureList) {
		tex->Release();
	}

}