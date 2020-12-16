/*
�R���|�[�l���g�N���X
*/

#pragma once

#include "Resource.h"

class Resource;

class Component {

private:

    // �L��
    bool Active;
    // ForDebug
    bool UsePanel;
    // �e
    Resource* pResource;

protected:

    // ��]�v�Z�p
    D3DXQUATERNION Quaternion;

public:

    Component() : Name("Component"), Active(true), UsePanel(false),pResource(nullptr){};

    // ���W
    D3DXVECTOR3 Position;
    // ��]
    D3DXVECTOR3 Rotation;
    // �X�P�[��
    D3DXVECTOR3 Scale;
    // ���O
    std::string Name;

    virtual void Init() = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void FixedUpdate() {};

    // ForDebug
    virtual void DataPanel() {};

    // Setter
    void SetUsePanel(bool val) { UsePanel = val; };
    void SetResource(Resource* target) { pResource = target; };
    // Getter
    bool GetUsePanel() { return UsePanel; };
    Resource* GetResource() { return pResource; };


};