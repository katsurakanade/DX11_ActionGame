#pragma once

#include "Resource.h"

class Resource;

class Component {

private:

	bool Active = true;

protected:

    D3DXQUATERNION Quaternion;

public:

    D3DXVECTOR3 Position;
    D3DXVECTOR3 Rotation;
    D3DXVECTOR3 Scale;

    std::string Name = "Component";

    virtual void Init() = 0;
    virtual void Uninit() = 0;
    virtual void Update(Resource* target) = 0;
};