#include "main.h"
#include "Renderer.h"
#include "AssimpModel.h"
#include "Asset.h"

void AssimpModel::Load(std::string FileName) {

	Assimp::Importer imp;

	const aiScene* scene = imp.ReadFile(FileName, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	assert(scene);

	Name = scene->mRootNode->mName.C_Str();

	this->Directory = FileName.substr(0, FileName.find_last_of('\\'));

	ProcessNode(scene->mRootNode, scene);

}

void AssimpModel::Unload() {

	for (int i = 0; i < Meshes.size(); i++)
	{
		Meshes[i].Close();
	}

}
std::string textype;

void AssimpModel::DrawConfig() {

	std::string str = u8"モデル情報: " + Name;
	ImGui::Begin(str.c_str());
	ImGui::SetWindowSize(ImVec2(300, 1000));

	ImGui::Text(u8"テクスチャ数 : %d ", textures_loaded.size());

	if (ImGui::TreeNode(u8"テクスチャファイル")) {
		for (int i = 0; i < textures_loaded.size(); i++) {
			ImGui::Text("%s", textures_loaded[i].path.c_str());
			ImGui::Image(textures_loaded[i].texture, ImVec2(100, 100));
		}
		ImGui::TreePop();

	}

	ImGui::Text(u8"メッシュ数 : %d", Meshes.size());

	if (ImGui::TreeNode(u8"メッシュ情報")) {

		for (int i = 0; i < Meshes.size(); i++) {
			if (ImGui::TreeNode(Meshes[i].Name.c_str())) {
				ImGui::Checkbox(u8"表示", &Meshes[i].Enable);
				ImGui::ColorEdit4(u8"カラー", Meshes[i].col);
				ImGui::SliderFloat3(u8"回転", Meshes[i].Rotation,-3.14f,3.14f);
				ImGui::Image(Meshes[i].Textures[0].texture, ImVec2(100, 100));
				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}

	ImGui::End();
}

void AssimpModel::Draw(D3DXMATRIX root) {

	if (DisplayConfig) {
		DrawConfig();
	}

	for (int i = 0; i < Meshes.size(); i++) {
		for (int j = 0; j < textures_loaded.size(); j++) {
			if (Meshes[i].Textures[0].path == textures_loaded[j].path) {

				if (DefaultTexture) {
					Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &textures_loaded[j].texture);
				}

				else if (!DefaultTexture) {
					if (textures_select[SelectTextureIndex].texture != NULL) {
						Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &textures_select[SelectTextureIndex].texture);
					}
				}

				D3DXMATRIX world, scale, rot, trans;
				D3DXMatrixScaling(&scale, Meshes[i].Scale.x, Meshes[i].Scale.y, Meshes[i].Scale.z);
				D3DXQuaternionRotationYawPitchRoll(&Meshes[i].Quaternion, Meshes[i].Rotation.y, Meshes[i].Rotation.x, Meshes[i].Rotation.z);
				D3DXMatrixRotationQuaternion(&rot, &Meshes[i].Quaternion);
				D3DXMatrixTranslation(&trans, Meshes[i].Position.x, Meshes[i].Position.y, Meshes[i].Position.z);
				world = scale * rot * trans;
				world *= root;
				Renderer::SetWorldMatrix(&world);

				if (Meshes[i].Enable){
					Meshes[i].Draw();
				}
			}
		}
	}

	

}

void AssimpModel::ProcessNode(aiNode* node, const aiScene* scene) {

	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
	
		Meshes.push_back(this->ProcessMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

Mesh AssimpModel::ProcessMesh(aiMesh* mesh, const aiScene* scene) {

	// Data to fill
	std::string name;
	std::vector<VERTEX_3D> vertices;
	std::vector<UINT> indices;
	std::vector<Texture> textures;
	MATERIAL material;

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		if (textype.empty()) {
			textype = determineTextureType(scene, mat);
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

		vertex.Normal.x = mesh->mNormals->x;
		vertex.Normal.y = mesh->mNormals->y;
		vertex.Normal.z = mesh->mNormals->z;

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

		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(aimaterial, aiTextureType_DIFFUSE, "texture_diffuse", scene);

		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		aiColor3D color;

		aimaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material.Ambient = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
		aimaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material.Diffuse = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
		aimaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material.Specular = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
		aimaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		material.Emission = D3DXCOLOR(color.r, color.g, color.b, 1.0f);
		material.Shininess = 225.0f;
	}

	

	return Mesh(name,vertices, indices, textures, material);
}

std::vector<Texture> AssimpModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene) {

	std::vector<Texture> textures;

	for (UINT i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (UINT j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			HRESULT hr;
			Texture texture;
			if (textype == "embedded compressed texture")
			{
				int textureindex = getTextureIndex(&str);
				texture.texture = getTextureFromModel(scene, textureindex);
			}
			else
			{
				std::string filename = std::string(str.C_Str());
				filename = Directory + '\\' + filename;
				std::wstring filenamews = std::wstring(filename.begin(), filename.end());
				
				hr = D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), filename.c_str(), NULL, NULL, &texture.texture, NULL);
				//assert(hr);
			}

			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

std::string AssimpModel::determineTextureType(const aiScene* scene, aiMaterial* mat) {

	aiString textypeStr;
	mat->GetTexture(aiTextureType_DIFFUSE, 0, &textypeStr);
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

int AssimpModel::getTextureIndex(aiString* str) {

	std::string tistr;
	tistr = str->C_Str();
	tistr = tistr.substr(1);
	return stoi(tistr);
}

ID3D11ShaderResourceView* AssimpModel::getTextureFromModel(const aiScene* scene, int textureindex) {

	HRESULT hr;
	ID3D11ShaderResourceView* texture;

	int* size = reinterpret_cast<int*>(&scene->mTextures[textureindex]->mWidth);

	hr = D3DX11CreateShaderResourceViewFromMemory(Renderer::GetDevice() , Renderer::GetDeviceContext(), *size, nullptr,nullptr, &texture,nullptr);

	return texture;

}

void AssimpModel::PushTextureSelect(int index) {
	Texture* t = new Texture();
	t->texture = Asset::GetTexture(index);
	textures_select.push_back(*t);
	delete t;
	t = nullptr;
}