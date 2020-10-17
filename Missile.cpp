#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Effect.h"
#include "Missile.h"
#include "Particle.h"


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
	mpEffect->Destroy();
}

void Missile::Update() {


	std::vector <Enemy*> es = Application::GetScene()->GetGameObjects<Enemy>(ObjectLayer);
	
	if (es.size() > 0) {

		if (mCurveProgress <= 1.0f) {
			mCurveProgress += 0.01f;
		}

		mpEffect->Position = Bezier(p0, p1, p2, mCurveProgress);

		// “G‚É“–‚½‚é
		if (mCurveProgress >= 1.0f) {
			mpEffect->Destroy();

			ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
			ParitcleSetting* setting = new ParitcleSetting;
			pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE));
			setting->Amount = 3000;
			setting->SpeedMinMaxX = D3DXVECTOR2(-0.5f, 0.5f);
			setting->SpeedMinMaxY = D3DXVECTOR2(-0.5f, 0.5f);
			setting->SpeedMinMaxZ = D3DXVECTOR2(0.0f, 1.0f);
			setting->LifeMinMax = D3DXVECTOR2(10.0f, 120.0f);
			setting->Size = 0.1f;
			pc->Create(setting);
			delete setting;
			pc->Position = es[mTargetIndex]->Position + D3DXVECTOR3(0, 3, 0);

			es[mTargetIndex]->mHp -= 3.0f;
			Destroy();
		}
	}

	else if (es.size() <= 0) {
		Destroy();
	}

}

void Missile::Render() {

}
