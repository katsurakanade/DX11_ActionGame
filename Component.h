/*
コンポーネントクラス
*/

#pragma once

#include "Resource.h"

class Resource;

class Component {

private:

    // 有効
    bool Active;
    // ForDebug
    bool UsePanel;
    // 親
    Resource* pResource;

protected:

    // 回転計算用
    D3DXQUATERNION Quaternion;

public:

    Component() : Name("Component"), Active(true), UsePanel(false),pResource(nullptr){};

    // 座標
    D3DXVECTOR3 Position;
    // 回転
    D3DXVECTOR3 Rotation;
    // スケール
    D3DXVECTOR3 Scale;
    // 名前
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