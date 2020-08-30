#pragma once

#include "main.h"
#include "Component.h"
#include <thread>
#include <chrono>
#include <functional>

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
    virtual void Update() {
        for (Component* c : Components) {
            c->Update(this);
        }
    };
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
        D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
        D3DXMatrixRotationQuaternion(&rot, &Quaternion);

        D3DXVECTOR3 forward;
        forward.x = rot._31;
        forward.y = rot._32;
        forward.z = rot._33;

        return forward;
    }

    void RotationAroundXZ(D3DXVECTOR3 target,float force) {
        float tx = target.x;
        float ty = target.z;
        float x0 = Position.x;
        float y0 = Position.z;

        Position.x = tx + (x0 - tx) * cos(D3DXToRadian(force)) - (y0 - ty) * sin(D3DXToRadian(force));
        Position.z = ty + (x0 - tx) * sin(D3DXToRadian(force)) + (y0 - ty) * cos(D3DXToRadian(force));
    }

    void RotationAroundXY(D3DXVECTOR3 target, float force) {
        float tx = target.x;
        float ty = target.y;
        float x0 = Position.x;
        float y0 = Position.y;

        Position.x = tx + (x0 - tx) * cos(D3DXToRadian(force)) - (y0 - ty) * sin(D3DXToRadian(force));
        Position.y = ty + (x0 - tx) * sin(D3DXToRadian(force)) + (y0 - ty) * cos(D3DXToRadian(force));
    }

    template <typename T>
    T* AddComponent() {
        T* Component = new T();
        Components.emplace_back(Component);
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