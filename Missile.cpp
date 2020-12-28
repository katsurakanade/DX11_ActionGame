#include "main.h"
#include "Renderer.h"
#include "Application.h"
#include "Missile.h"
#include "Particle.h"
#include "EnemyBehavior.h"
#include "ImageManager.h"


D3DXVECTOR3 Bezier(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, float t)
{
	D3DXVECTOR3 p0p1 = (1 - t) * p0 + t * p1;
	D3DXVECTOR3 p1p2 = (1 - t) * p1 + t * p2;
	D3DXVECTOR3 result = (1 - t) * p0p1 + t * p1p2;
	return result;
}

void Missile::Init() {

	Sprite* effect = Application::GetScene()->AddGameObject<Sprite>(EffectLayer);
	effect->GetComponent<ImageManager>()->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::EXPLOSION));
	effect->GetComponent<ImageManager>()->SetBillBoard(true);
	effect->GetComponent<ImageManager>()->SetAnimationSprite(true);
	effect->GetComponent<ImageManager>()->SetHW(8, 6);
	effect->GetComponent<ImageManager>()->SetAnimationSpeed(5.0f);
	effect->Position = Position;
	effect->Scale = D3DXVECTOR3(3, 3, 3);
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
	std::sort(es.begin(), es.end(), [](Enemy* lh, Enemy* rh) {return lh->GetComponent<EnemyBehavior>()->GetLengthToPlayer() < rh->GetComponent<EnemyBehavior>()->GetLengthToPlayer(); });
	
	if (es.size() > 0) {

		if (mCurveProgress <= 1.0f) {
			mCurveProgress += 1.0f * Time::GetDeltaTime();
		}

		mpEffect->Position = Bezier(p0, p1, p2, mCurveProgress);

		// “G‚É“–‚½‚é
		if (mCurveProgress >= 1.0f) {
			mpEffect->Destroy();
			ParticleSystem* pc = Application::GetScene()->AddGameObject<ParticleSystem>(EffectLayer);
			pc->Create(&FileManager::ReadParticleJSON("asset\\json_particle\\PlayerAttack_Simple_Particle.json"));
			pc->SetTexture(Application::GetAsset()->GetTexture((int)TEXTURE_ENUM_GAME::PARTICLE));
			pc->Position = es[mTargetIndex]->Position + D3DXVECTOR3(0, 3, 0);
			es[mTargetIndex]->GetComponent<EnemyBehavior>()->mHp -= 3.0f;
			Destroy();
		}
	}

	else if (es.size() <= 0) {
		Destroy();
	}

}

void Missile::Render() {

}
