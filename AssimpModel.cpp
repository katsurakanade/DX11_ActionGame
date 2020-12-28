#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "AssimpModel.h"
#include "Debug.h"
#include "Shader.h"

bool AssimpModel::Load(std::string FileName) {

	mScene = aiImportFile(FileName.c_str(), aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);

	if (mScene == nullptr) 
		return false;

	mName = mScene->mRootNode->mName.C_Str();

	this->mDirectory = FileName.substr(0, FileName.find_last_of('\\'));

	ProcessNode(mScene->mRootNode, mScene);

	return true;
}

bool AssimpModel::LoadAnimation(std::string Filename,std::string name) {

	auto file = aiImportFile(Filename.c_str(), aiProcess_ConvertToLeftHanded);

	if (file == nullptr)
		return false;

	mAnimation[name] = file;
	
	return true;
	
}

void AssimpModel::Unload() {

	for (unsigned int i = 0; i < mMeshes.size(); i++)
	{
		mMeshes[i]->Close();
		delete mMeshes[i];
		mMeshes[i] = nullptr;
	}

	mScene->~aiScene();
	
	mMeshes.clear();
	mMeshes.shrink_to_fit();

	mTexturesLoaded.clear();
	mTexturesLoaded.shrink_to_fit();

	mTexturesLoaded_Normal.clear();
	mTexturesLoaded_Normal.shrink_to_fit();

	mTexturesSelect.clear();
	mTexturesSelect.shrink_to_fit();


}

std::string textype;

void AssimpModel::DrawConfig() {

	ImGui::Begin(mResourceName.c_str());

	if (ImGui::TreeNode(u8"モデル")) {

		ImGui::Text(u8"テクスチャ数 : %d ", mTexturesLoaded.size() + mTexturesLoaded_Normal.size());
		if (ImGui::TreeNode(u8"テクスチャファイル")) {
			for (unsigned int i = 0; i < mTexturesLoaded.size(); i++) {
				ImGui::Text(u8"タイプ : %s", mTexturesLoaded[i].type.c_str());
				ImGui::Text(u8"パス : %s", mTexturesLoaded[i].path.c_str());
				ImGui::Image(mTexturesLoaded[i].texture, ImVec2(100, 100));
			}
			for (unsigned int i = 0; i < mTexturesLoaded_Normal.size(); i++) {
				ImGui::Text(u8"タイプ : %s", mTexturesLoaded_Normal[i].type.c_str());
				ImGui::Text(u8"パス : %s", mTexturesLoaded_Normal[i].path.c_str());
				ImGui::Image(mTexturesLoaded_Normal[i].texture, ImVec2(100, 100));
			}
			ImGui::TreePop();

		}

		ImGui::Text(u8"メッシュ数 : %d", mMeshes.size());
		if (ImGui::TreeNode(u8"メッシュ情報")) {

			for (unsigned int i = 0; i < mMeshes.size(); i++) {
				std::string name = mMeshes[i]->Name + std::to_string(i);
				if (ImGui::TreeNode(name.c_str())) {
					ImGui::Checkbox(u8"表示", &mMeshes[i]->Enable);
					ImGui::ColorEdit4(u8"カラー", mMeshes[i]->col);
					ImGui::Image(mMeshes[i]->Textures[0].texture, ImVec2(100, 100));
					if (Anicmatrixion) {
						ImGui::Text("Bone :  %d", mMeshes[i]->mBone.size());
						ImGui::Text("Deform Vertex : %d", mMeshes[i]->mDeformVertex.size());
					}
					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}
		ImGui::TreePop();
	}

	ImGui::End();
}

void AssimpModel::Update(const char* animationname,int frame){

	if (animationname != "" && !mAnimation[animationname]->HasAnimations()) {
		return;
	}

	aiAnimation* animation = mAnimation[animationname]->mAnimations[0];

	for (unsigned int c = 0; c < animation->mNumChannels; c++) {

		aiNodeAnim* node = animation->mChannels[c];

		int f;
		f = frame % node->mNumRotationKeys;
		aiQuaternion rot = node->mRotationKeys[f].mValue;

		f = frame % node->mNumPositionKeys;
		aiVector3D pos = node->mPositionKeys[f].mValue;

		for (Mesh* m : mMeshes) {
			BONE* bone = &m->mBone[node->mNodeName.C_Str()];
			m->UpdateBoneMatrix(mScene->mRootNode, aiMatrix4x4());
			bone->mAnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
		}

	}

	for (Mesh* m : mMeshes) {
		m->Update();
	}
}

void AssimpModel::Update(const char* animationname1, const char* animationname2,float BlendRate, int frame) {


	if (!mAnimation[animationname1]->HasAnimations()) {
		return;
	}

	if (!mAnimation[animationname2]->HasAnimations()) {
		return;
	}

	aiAnimation* animation_1 = mAnimation[animationname1]->mAnimations[0];
	aiAnimation* animation_2 = mAnimation[animationname2]->mAnimations[0];

	for (unsigned int c = 0; c < animation_1->mNumChannels; c++) {

		aiNodeAnim* node_1 = animation_1->mChannels[c];
		aiNodeAnim* node_2 = animation_2->mChannels[c];

		int f;

		f = frame % node_1->mNumRotationKeys;
		aiQuaternion rot_1 = node_1->mRotationKeys[f].mValue;
		f = frame % node_1->mNumPositionKeys;
		aiVector3D pos_1 = node_1->mPositionKeys[f].mValue;

		f = frame % node_2->mNumRotationKeys;
		aiQuaternion rot_2 = node_2->mRotationKeys[f].mValue;
		f = frame % node_2->mNumPositionKeys;
		aiVector3D pos_2 = node_2->mPositionKeys[f].mValue;

		aiVector3D pos = pos_1 * (1.0f - BlendRate) + pos_2 * BlendRate;
		aiQuaternion rot;
		aiQuaternion::Interpolate(rot, rot_1, rot_2, BlendRate);

		for (Mesh* m : mMeshes) {
			BONE* bone = &m->mBone[node_1->mNodeName.C_Str()];
			bone->mAnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
			m->UpdateBoneMatrix(mScene->mRootNode, aiMatrix4x4());
		}
	}

	for (Mesh* m : mMeshes) {
		m->Update();
	}
}

void AssimpModel::Draw(D3DXMATRIX root) {

	if (DisplayConfig) {
		DrawConfig();
	}

	for (unsigned int i = 0; i < mMeshes.size(); i++) {
		for (unsigned int j = 0; j < mTexturesLoaded.size(); j++) {
			if (mMeshes[i]->Textures[0].path == mTexturesLoaded[j].path) {

				if (DefaultTexture) {
					Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexturesLoaded[j].texture);
 				}

				else if (!DefaultTexture) {
					if (SelectTextureIndex != 0 && mTexturesSelect[SelectTextureIndex].texture != NULL) {
						Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexturesSelect[SelectTextureIndex].texture);
					}
				}
			}
		}

		for (unsigned int j = 0; j < mTexturesLoaded_Normal.size(); j++) {
			Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &mTexturesLoaded_Normal[j].texture);
		}

		if (mMeshes[i]->Enable) {
			mMeshes[i]->Draw();
		}
	}

	

}

void AssimpModel::ProcessNode(aiNode* node, const aiScene* scene) {

	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
	
		mMeshes.push_back(this->ProcessMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}

}

Mesh* AssimpModel::ProcessMesh(aiMesh* mesh, const aiScene* scene) {

	// Data to fill
	std::string name;
	std::vector<VERTEX_3D> vertices;
	std::vector<UINT> indices;
	std::vector<Texture> textures;
	std::vector<Texture> textures_normal;
	std::vector <DEFORM_VERTEX> DeformVertex;
	std::unordered_map  <std::string, BONE> Bone;
	MATERIAL  cmatrixerial;

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		if (textype.empty()) {
			textype = DetermineTextureType(scene, mat);
		}
	} 

	name = mesh->mName.C_Str();

	// Vertex
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		VERTEX_3D vertex;

		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.TexCoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertex.Normal.x = mesh->mNormals[i].x;
		vertex.Normal.y = mesh->mNormals[i].y;
		vertex.Normal.z = mesh->mNormals[i].z;

		vertex.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices.push_back(vertex);
	}

	// Index
	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	
	// Material
	if (mesh->mMaterialIndex >= 0)
	{

		aiMaterial* aimaterial = scene->mMaterials[mesh->mMaterialIndex];

		// ディフューズマップ
		std::vector<Texture> diffuseMaps = this->LoadMatrixerialTextures(aimaterial, aiTextureType_DIFFUSE, "Diffuse", scene);
		// 法線マップ
		std::vector<Texture> normalMaps = this->LoadMatrixerialTextures(aimaterial, aiTextureType_HEIGHT, "Normal", scene);

		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures_normal.insert(textures_normal.end(), normalMaps.begin(), normalMaps.end());

		aiColor3D color;

		aimaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		cmatrixerial.Ambient = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
		aimaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		cmatrixerial.Diffuse = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
		aimaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		cmatrixerial.Specular = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
		aimaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		cmatrixerial.Emission = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
		cmatrixerial.Shininess = 225.0f;
	}

	if (Anicmatrixion) {
		for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
			DEFORM_VERTEX deform;
			deform.Position = mesh->mVertices[v];
			deform.Normal = mesh->mNormals[v];
			deform.mBoneNum = 0;

			for (unsigned int b = 0; b < 4; b++) {
				
				deform.mBoneName[b] = "";
				deform.mBoneWeight[b] = 0.0f;
			}

			DeformVertex.push_back(deform);
		}

		for (unsigned int b = 0; b < mesh->mNumBones; b++) {
			aiBone* bone = mesh->mBones[b];
			Bone[bone->mName.C_Str()].mOffsetMatirx = bone->mOffsetMatrix;

			for (unsigned int w = 0; w < bone->mNumWeights; w++) {
				aiVertexWeight weight = bone->mWeights[w];

				int num = DeformVertex[weight.mVertexId].mBoneNum;
				DeformVertex[weight.mVertexId].mBoneWeight[num] = weight.mWeight;
				DeformVertex[weight.mVertexId].mBoneName[num] = bone->mName.C_Str();
				DeformVertex[weight.mVertexId].mBoneNum++;

				assert(DeformVertex[weight.mVertexId].mBoneNum <= 4);

			}
		}

		CreateBone(scene->mRootNode, Bone);


		return new Mesh(name, vertices, indices, textures, cmatrixerial, DeformVertex, Bone);
	}

	return new Mesh(name, vertices, indices, textures,textures_normal, cmatrixerial);

}

std::vector<Texture> AssimpModel::LoadMatrixerialTextures(aiMaterial* cmatrix, aiTextureType type, std::string typeName, const aiScene* scene) {

	std::vector<Texture> textures;

	for (UINT i = 0; i < cmatrix->GetTextureCount(type); i++)
	{
		aiString str;
		cmatrix->GetTexture(type, i, &str);
		bool skip = false;
		for (UINT j = 0; j < mTexturesLoaded.size(); j++)
		{
			if (std::strcmp(mTexturesLoaded[j].path.c_str(), str.C_Str()) == 0)
			{
				textures.push_back(mTexturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{  
			HRESULT hr;
			Texture texture;
			if (textype == "embedded compressed texture")
			{
				int textureindex = GetTextureIndex(&str);
				texture.texture = GetTextureFromModel(scene, textureindex);
			}
			{

				std::string filename = std::string(str.C_Str());
				filename = mDirectory + '\\' + filename;
				if (str.data[0] == 46) {
					int id = atoi(&str.data[1]);
					hr = D3DX11CreateShaderResourceViewFromMemory(Renderer::GetDevice(), (const unsigned char*)scene->mTextures[id]->pcData, scene->mTextures[id]->mWidth, NULL, NULL, &texture.texture, NULL);
				}
				else {
					hr = D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), filename.c_str(), NULL, NULL, &texture.texture, NULL);
				}
				
			}

			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			this->mTexturesLoaded.push_back(texture);

		}
	}
	return textures;
}

std::string AssimpModel::DetermineTextureType(const aiScene* scene, aiMaterial* cmatrix) {

	aiString textypeStr;
	cmatrix->GetTexture(aiTextureType_DIFFUSE, 0, &textypeStr);
	std::string textypeteststr = textypeStr.C_Str();
	if (textypeteststr == "*0" || textypeteststr == "*1" || textypeteststr == "*2" || textypeteststr == "*3" || textypeteststr == "*4" || textypeteststr == "*5")
	{
		if (scene->mTextures[0]->mHeight == 0)
		{
			return "embedded compressed texture";
		}
		else
		{
			return "embedded non-compressed texture";
		}
	}
	if (textypeteststr.find('.') != std::string::npos)
	{
		return "textures are on disk";
	}

	return "";
}

int AssimpModel::GetTextureIndex(aiString* str) {

	std::string tistr;
	tistr = str->C_Str();
	tistr = tistr.substr(1);
	return stoi(tistr);
}

ID3D11ShaderResourceView* AssimpModel::GetTextureFromModel(const aiScene* scene, int textureindex) {

	HRESULT hr;
	ID3D11ShaderResourceView* texture;

	int* size = reinterpret_cast<int*>(&scene->mTextures[textureindex]->mWidth);

	hr = D3DX11CreateShaderResourceViewFromMemory(Renderer::GetDevice() , Renderer::GetDeviceContext(), *size, nullptr,nullptr, &texture,nullptr);

	return texture;

}

void AssimpModel::PushTextureSelect(Asset* asset,int index) {
	Texture* t = new Texture();
	t->texture = asset->GetTexture(index);
	mTexturesSelect.push_back(*t);
	delete t;
	t = nullptr;
}

void AssimpModel::CreateBone(aiNode* node, std::unordered_map  <std::string, BONE> tBone) {
	BONE bone;
	tBone[node->mName.C_Str()] = bone;

	for (unsigned int n = 0; n < node->mNumChildren; n++) {
		CreateBone(node->mChildren[n],tBone);
	}
}

void AssimpModel::SetColorAll(D3DXCOLOR col) {
	for (unsigned int i = 0; i < mMeshes.size(); i++) {
		mMeshes[i]->col[0] = col.r;
		mMeshes[i]->col[1] = col.g;
		mMeshes[i]->col[2] = col.b;
		mMeshes[i]->col[3] = col.a;
	}
}
