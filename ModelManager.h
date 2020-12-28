#pragma once

#include "Component.h"

class ModelManager : public Component
{

private:

	// ���f��
	AssimpModel* mModel;
	// �A�j���[�V�����|�C���^
	Animation* mpAnimation;

public:

	ModelManager() : mModel(nullptr),mpAnimation(nullptr) {};

	void Init();
	void Uninit();
	void Update();
	void FixedUpdate();

	void Render(D3DXMATRIX world);
	
	// Setter
	void SetModel(AssimpModel* model) { mModel = model; };
	// Getter
	AssimpModel* GetModel() { return mModel; };

};

