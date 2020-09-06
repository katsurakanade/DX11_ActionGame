#pragma once

#include "Resource.h"

class Resource;

class Component {

private:

	bool Active = true;
    bool UsePanel = false;
    Resource* pResource;

protected:

    D3DXQUATERNION Quaternion;

public:

    D3DXVECTOR3 Position;
    D3DXVECTOR3 Rotation;
    D3DXVECTOR3 Scale;

    std::string Name = "Component";

    virtual void Init() = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;

    virtual void DataPanel() = 0;

    void SetUsePanel(bool val) { UsePanel = val; };
    bool GetUsePanel() { return UsePanel; };

    void SetResource(Resource* target) { pResource = target; };
    Resource* GetResource() { return pResource; };


};