#include "main.h"
#include "renderer.h"
#include "MeshField.h"
#include "Application.h"
#include "Shader.h"
#include "FileManger.h"
#include "Grass.h"
#include <random>

float MeshField::HeightMap[21][21];
std::random_device rnd;

void MeshField::Init() {

	FileManger::Read("terrain.dat", MeshField::HeightMap);
	FileManger::ReadResource("grass.json");

	Name = "MeshField";

	std::random_device rd;
	std::default_random_engine gen = std::default_random_engine(rd());
	std::uniform_real_distribution<float> dis(0.1f, 0.5f);

	for (int x = 0; x <= 20; x++) {
		for (int z = 0; z <= 20; z++) {
			/*float y = sinf(x * 0.3f) * 5.0f;*/
			float y = HeightMap[x][z];
			mVertex[x][z].Position = D3DXVECTOR3((x - 10) * 10.0f, y, (z - 10) * -10.0f);
			mVertex[x][z].Normal = D3DXVECTOR3(0, 1, 0);
			mVertex[x][z].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
			mVertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
		}
	}

	for (int x = 1; x <= 19; x++) {
		for (int z = 1; z <= 19; z++) {
			D3DXVECTOR3 vx, vz, vn;
			vx = mVertex[x + 1][z].Position - mVertex[x - 1][z].Position;
			vz = mVertex[x][z - 1].Position - mVertex[x][z + 1].Position;
			D3DXVec3Cross(&vn, &vz, &vx);
			D3DXVec3Normalize(&vn, &vn);
			mVertex[x][z].Normal = vn;
		}
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mVertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

	// Index Buffer
	{
		unsigned int index[(22 * 2) * 20 - 2];
		int i = 0;
		for (int x = 0; x < 20; x++) {
			for (int z = 0; z < 21; z++) {
				index[i] = x * 21 + z;
				i++;
				index[i] = (x + 1) * 21 + z;
				i++;
			}
			if (x == 19) {
				break;
			}

			index[i] = (x + 1) * 21 + 20;
			i++;
			index[i] = (x + 1) * 21;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22*2) * 20 - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mIndexBuffer);
	}

	mTexture.push_back(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::DIRT));

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXQuaternionIdentity(&Quaternion);
}

void MeshField::Unint() {
	mVertexBuffer->Release();
	mIndexBuffer->Release();
}

void MeshField::Update() {

	ImGui::Begin(u8"地形ツール",nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::PushItemWidth(30);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu(u8"マップ"))
		{
			if (ImGui::MenuItem(u8"Save")) {
				FileManger::Write("terrain.dat", MeshField::HeightMap);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"マップオブジェク"))
		{
			if (ImGui::MenuItem(u8"Save")) {
				std::vector<Grass*> grasslist = Application::GetScene()->GetGameObjects<Grass>(EffectLayer);
				FileManger::WriteResource("grass.json", grasslist);
			}
	
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	if (ImGui::TreeNode(u8"マップデータ")) {
		for (int x = 0; x < 21; x++) {
			for (int z = 0; z < 21; z++) {
				std::string str = std::to_string(x) + "," + std::to_string(z);
				ImGui::SliderFloat(str.c_str(), &HeightMap[z][x], -20.0f, 20.0f, "%.1f");
				ImGui::SameLine();
			}
			ImGui::NewLine();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(u8"マップオブジェクト追加")) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.5f, 0.0f, 1.0f });
		if (ImGui::Button(u8"草")) {
			Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
			Grass* g = Application::GetScene()->AddGameObject<Grass>(EffectLayer);
			g->Name = "Grass_" + std::to_string(rnd());
			g->Tag = "Grass";
			g->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PLANT));
			g->Position = p->Position;
		}
		ImGui::SameLine();
		if (ImGui::Button(u8"岩")) {
			Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
			Grass* g = Application::GetScene()->AddGameObject<Grass>(EffectLayer);
			g->Name = "Stone_" + std::to_string(rnd());
			g->Tag = "Stone";
			g->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::STONE));
			g->Position = p->Position;
			g->Scale = D3DXVECTOR3(5, 5, 1);
		}
		ImGui::PopStyleColor();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(u8"マップオブジェクトリスト")) {
		std::vector<Grass*> grasslist = Application::GetScene()->GetGameObjects<Grass>(EffectLayer);
		for (unsigned int i = 0; i < grasslist.size(); i++) {
			if (ImGui::TreeNode(grasslist[i]->Name.c_str())) {
				ImGui::PushItemWidth(1000);
				ImGui::SliderFloat3(u8"座標", grasslist[i]->Position, -5000.0f, 5000.0f,"%.1f",10.0f);
				ImGui::SliderFloat3(u8"回転", grasslist[i]->Rotation, -3.14f, 3.14f);
				ImGui::SliderFloat3(u8"スケール", grasslist[i]->Scale, 0.1f, 10.0f);
				if (ImGui::Button(u8"削除")) {
					grasslist[i]->Destroy();
				}
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	if (ImGui::Button(u8"変更")) {
		ResetField();
	}
	ImGui::End();
}

void MeshField::Render() {

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &Quaternion);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer,DXGI_FORMAT_R32_UINT,0);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Shininess = 225;
	Renderer::SetMaterial(material);

	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mTexture[0]);

	if (!Renderer::mLineMode) {
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}

	else {
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}

	Shader::Use(SHADER_TYPE_VSPS::Default);


	Renderer::GetDeviceContext()->DrawIndexed((22*2) * 20 - 2,0, 0);
	

}

void MeshField::ResetField() {

	mVertexBuffer->Release();

	for (int x = 0; x <= 20; x++) {
		for (int z = 0; z <= 20; z++) {
			/*float y = sinf(x * 0.3f) * 5.0f;*/
			float y = HeightMap[x][z];
			mVertex[x][z].Position = D3DXVECTOR3((x - 10) * 10.0f, y, (z - 10) * -10.0f);
			mVertex[x][z].Normal = D3DXVECTOR3(0, 1, 0);
			mVertex[x][z].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
			mVertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
		}
	}

	for (int x = 1; x <= 19; x++) {
		for (int z = 1; z <= 19; z++) {
			D3DXVECTOR3 vx, vz, vn;
			vx = mVertex[x + 1][z].Position - mVertex[x - 1][z].Position;
			vz = mVertex[x][z - 1].Position - mVertex[x][z + 1].Position;
			D3DXVec3Cross(&vn, &vz, &vx);
			D3DXVec3Normalize(&vn, &vn);
			mVertex[x][z].Normal = vn;
		}
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mVertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);
}

float MeshField::GetHeight(D3DXVECTOR3 pos) {

	int x, z;
	x = pos.x / 10.0f + 10.0f;
	z = pos.z / -10.0f + 10.0f;

	D3DXVECTOR3 pos0, pos1, pos2, pos3;

	pos0 = mVertex[x][z].Position;
	pos1 = mVertex[x + 1][z].Position;
	pos2 = mVertex[x][z+1].Position;
	pos3 = mVertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;

	v12 = pos2 - pos1;
	v1p = pos - pos1;

	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;

	if (c.y > 0.0f) {
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else {
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	py = -((pos.x - pos1.x) * n.x + (pos.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;
}