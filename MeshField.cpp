#include "main.h"
#include "renderer.h"
#include "MeshField.h"
#include "Application.h"
#include "Shader.h"
#include "FileManger.h"
#include "Grass.h"
#include "Props.h"
#include <random>

float MeshField::HeightMap[FIELD_X][FIELD_X];

void MeshField::Init() {

	// �}�b�v��̃I�u�W�F�N�g���[�h
	FileManger::ReadResource("grass.json");
	FileManger::ReadResource("rock.json");
	// �}�b�v���[�h�i�摜�j
	FileManger::ReadImageMap("asset/texture/map.bmp",MeshField::HeightMap);

	Name = "MeshField";

	// ���_
	for (int x = 0; x <= FIELD_X - 1; x++) {
		for (int z = 0; z <= FIELD_X - 1; z++) {
			float y = HeightMap[x][z];
			mVertex[x][z].Position = D3DXVECTOR3((x - 10) * 10.0f, y, (z - 10) * -10.0f);
			mVertex[x][z].Normal = D3DXVECTOR3(0, 1, 0);
			mVertex[x][z].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
			mVertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
		}
	}

	// �@��
	for (int x = 1; x <= FIELD_X - 2; x++) {
		for (int z = 1; z <= FIELD_X - 2; z++) {
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
	bd.ByteWidth = sizeof(VERTEX_3D) * FIELD_X * FIELD_X;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mVertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);

	// Index Buffer
	{
		unsigned int index[((FIELD_X+1) * 2) * (FIELD_X-1) - 2];
		int i = 0;
		for (int x = 0; x < FIELD_X - 1; x++) {
			for (int z = 0; z < FIELD_X; z++) {
				index[i] = x * FIELD_X + z;
				i++;
				index[i] = (x + 1) * FIELD_X + z;
				i++;
			}
			if (x == FIELD_X-2) {
				break;
			}

			index[i] = (x + 1) * FIELD_X + (FIELD_X - 1);
			i++;
			index[i] = (x + 1) * FIELD_X;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * (((FIELD_X + 1)*2) * (FIELD_X - 1) - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mIndexBuffer);
	}

	// �摜
	mTexture.push_back(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::DIRT));
	mTexture.push_back(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::GRASS));

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

	ImGui::Begin(u8"�n�`�c�[��",nullptr, ImGuiWindowFlags_MenuBar);
	ImGui::PushItemWidth(30);
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu(u8"�}�b�v�I�u�W�F�N"))
		{
			if (ImGui::MenuItem(u8"Save")) {
				std::vector<Grass*> grasslist = Application::GetScene()->GetGameObjects<Grass>(EffectLayer);
				FileManger::WriteResource("grass.json", grasslist);
				std::vector<Props*> propslist = Application::GetScene()->GetGameObjects<Props>(ObjectLayer);
				FileManger::WriteResource("rock.json", propslist);
			}
	
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	if (ImGui::TreeNode(u8"�}�b�v�I�u�W�F�N�g�ǉ�")) {
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.5f, 0.0f, 1.0f });
		if (ImGui::Button(u8"��")) {
			Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
			Grass* g = Application::GetScene()->AddGameObject<Grass>(EffectLayer);
			g->Name = "Grass_" + std::to_string(Application::RandomDevice());
			g->Tag = "Grass";
			g->Type = "BillBoard";			
			g->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PLANT));
			g->Position = p->Position;
		}
		ImGui::SameLine();
		if (ImGui::Button(u8"��")) {
			Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);
			Props* rock = Application::GetScene()->AddGameObject<Props>(ObjectLayer);
			rock->SetModel(Application::GetAsset()->GetAssimpModel((int)ASSIMP_MODEL_ENUM_GAME::ROCK));
			rock->Name = "Rock_" + std::to_string(Application::RandomDevice());
			rock->Tag = "Rock";
			rock->Type = "Object";
			rock->Position = p->Position;
			rock->Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
		}
		ImGui::PopStyleColor();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode(u8"�}�b�v�I�u�W�F�N�g���X�g")) {
		std::vector<Grass*> grasslist = Application::GetScene()->GetGameObjects<Grass>(EffectLayer);
		std::vector<Props*> propslist = Application::GetScene()->GetGameObjects<Props>(ObjectLayer);
		for (unsigned int i = 0; i < grasslist.size(); i++) {
			if (ImGui::TreeNode(grasslist[i]->Name.c_str())) {
				ImGui::PushItemWidth(1000);
				ImGui::SliderFloat3(u8"���W", grasslist[i]->Position, -200.0f, 200.0f, "%.1f",1.0f);
				ImGui::SliderFloat3(u8"��]", grasslist[i]->Rotation, -3.14f, 3.14f);
				ImGui::SliderFloat3(u8"�X�P�[��", grasslist[i]->Scale, 0.1f, 10.0f);
				if (ImGui::Button(u8"�폜")) {
					grasslist[i]->Destroy();
				}
				ImGui::TreePop();
			}
		}
		for (unsigned int i = 0; i < propslist.size(); i++) {
			if (ImGui::TreeNode(propslist[i]->Name.c_str())) {
				ImGui::PushItemWidth(1000);
				ImGui::SliderFloat3(u8"���W", propslist[i]->Position, -200.0f, 200.0f, "%.1f", 1.0f);
				ImGui::SliderFloat3(u8"��]", propslist[i]->Rotation, -3.14f, 3.14f);
				ImGui::SliderFloat3(u8"�X�P�[��", propslist[i]->Scale, 0.1f, 10.0f);
				if (ImGui::Button(u8"�폜")) {
					propslist[i]->Destroy();
				}
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
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

	Renderer::GetDeviceContext()->DrawIndexed(((FIELD_X + 1)*2) * (FIELD_X - 1) -2,0, 0);
	
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