#pragma once

#include "Component.h"

class ModelManager : public Component
{

private:

	// ���f��
	AssimpModel* mModel;
	// �A�j���[�V�����|�C���^
	Animation* mpAnimation;
	// �Ɨ��̃��f��(���[�h�K�v)
	bool mIndependence;

public:

	ModelManager() : mModel(nullptr), mpAnimation(nullptr), mIndependence(false) {};

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();

	void Render(D3DXMATRIX world);

	void LoadModelWithAnimation(std::string path);
	
	// Setter
	void SetModel(AssimpModel* model) { mModel = model; };
	// Getter
	AssimpModel* GetModel() { return mModel; };

};

