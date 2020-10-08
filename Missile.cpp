#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Effect.h"
#include "Missile.h"


D3DXVECTOR3 Bezier(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, float t)
{
	D3DXVECTOR3 p0p1 = (1 - t) * p0 + t * p1;
	D3DXVECTOR3 p1p2 = (1 - t) * p1 + t * p2;
	D3DXVECTOR3 result = (1 - t) * p0p1 + t * p1p2;
	return result;
}

void Missile::Init() {

	Effect* effect = Application::GetScene()->AddGameObject<Effect>(EffectLayer);
	effect->Position = Position;
	effect->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::EXPLOSION));
	effect->SetHW(8, 6);
	effect->SetAnimeSpeed(5.0f);
	effect->Scale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	mpEffect = effect;

	Enemy* e = Application::GetScene()->GetGameObject<Enemy>(ObjectLayer);
	Player* p = Application::GetScene()->GetGameObject<Player>(ObjectLayer);

	p0 = p->Position;
	p1 = p->Position + D3DXVECTOR3(0, 50, 0);
	p2 = e->Position;
}

void Missile::Uninit() {

}

void Missile::Update() {

	Enemy* e = Application::GetScene()->GetGameObject<Enemy>(ObjectLayer);
	p2 = e->Position;

	if (mCurveProgress <= 1.0f) {
		mCurveProgress += 0.01f;
	}

	mpEffect->Position = Bezier(p0, p1,p2, mCurveProgress);

	if (mCurveProgress >= 1.0f) {
		mpEffect->Destroy();
		Destroy();
	}

}

void Missile::Render() {

}
