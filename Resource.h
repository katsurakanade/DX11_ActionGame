#pragma once

#include "main.h"
#include "Component.h"

class Resource {

private:

    bool Alive = true;
    bool Active = true;

protected:

    D3DXQUATERNION Quaternion;

    std::vector <Component*> Components;
  
public:
    
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Rotation;
    D3DXVECTOR3 Scale;

    std::string Name = "Object";

    virtual void Init() {
        for (Component* c : Components) {
            c->Init();
        }
    };
    virtual void Uninit() {
        for (Component* c : Components) {
            c->Uninit();
        }
    };
    virtual void Update() = 0;
    virtual void Render() = 0;

    void SetActive(bool active) { this->Active = active; };
    void Destroy() { this->Alive = false; };

    bool GetActive() { return this->Active; };

    bool Remove() {
        if (!Alive) {
            Uninit();
            delete this;
            return true;
        }
        else {
            return false;
        }
    }

    D3DXVECTOR3 GetForward() {
        D3DXMATRIX rot;
        D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);

        D3DXVECTOR3 forward;
        forward.x = rot._31;
        forward.y = rot._32;
        forward.z = rot._33;

        return forward;
    }

    template <typename T>
    T* AddComponent() {
        T* Component = new T();
        Components.push_back(Component);
        Component->Init();
        return Component;
    };

    template <typename T>
    T* GetComponent() {
        for (Component* obj : Components) {
            if (typeid(*obj) == typeid(T)) {
                return (T*)obj;
            }
        }
        return NULL;
    };
};