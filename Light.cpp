#include "main.h"
#include "Renderer.h"
#include "Light.h"

void Light::Init() {

	Name = "Light";

	source = new LIGHT();

	source->Direction = D3DXVECTOR4(0.0f, 1.0f, -0.1f, 0.0f);
	D3DXVec4Normalize(&source->Direction, &source->Direction);
	source->Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	source->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	source->Enable = true;

}

void Light::Uninit() {

	if (source) {
		delete source;
		source = nullptr;
	}
}

void Light::Update() {

	ImGui::Begin(u8"ƒ‰ƒCƒg");
	ImGui::SetWindowSize(ImVec2(500, 300));

	float dir[3] = { source->Direction.x ,source->Direction.y ,source->Direction.z };
	ImGui::SliderFloat3("Direction", dir, -1.0f, 1.0f);
	source->Direction = D3DXVECTOR4(dir[0], dir[1], dir[2], 0.0f);

	float a[3] = { source->Ambient.r ,source->Ambient.g ,source->Ambient.b };
	ImGui::SliderFloat3("Ambient", a, 0.0f, 1.0f);
	source->Ambient = D3DXCOLOR(a[0], a[1], a[2], 1.0f);

	float d[3] = { source->Diffuse.r ,source->Diffuse.g ,source->Diffuse.b };
	ImGui::SliderFloat3("Diffuse", d, 0.0f, 1.0f);
	source->Diffuse = D3DXCOLOR(d[0], d[1], d[2], 1.0f);

	ImGui::End();

}

void Light::Render() {

	Renderer::SetLight(*source);

}


