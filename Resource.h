/*
���\�[�X�N���X
*/
#pragma once

#include "main.h"
#include "Component.h"
#include <thread>
#include <chrono>
#include <functional>

class Resource {

private:

    // �����Ă��� 
    bool Alive = true;
    // �L��
    bool Active = true;

protected:

    // ��]�v�Z�p
    D3DXQUATERNION Quaternion;
    // �R���|�[�l���g
    std::vector <Component*> Components;
    // ���[���h�}�g���N�X����
    D3DXMATRIX MakeWorldMatrix() {
        D3DXMATRIX world, scale, rot, trans;
        D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
        D3DXQuaternionRotationYawPitchRoll(&Quaternion, Rotation.y, Rotation.x, Rotation.z);
        D3DXMatrixRotationQuaternion(&rot, &Quaternion);
        D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
        world = scale * rot * trans;
        return world;
    };
  
public:

    Resource() :Name("Object"),Tag("Untagger"),Type("Object") {};
    
    // ���W
    D3DXVECTOR3 Position;
    // ��]
    D3DXVECTOR3 Rotation;
    // �X�P�[��
    D3DXVECTOR3 Scale;
    // ���O
    std::string Name;
    // �^�O
    std::string Tag;
    // �^�C�v
    std::string Type;
    // �p�[�l��
    bool Panel;

    virtual void Init() {
        for (Component* c : Components) {
            c->Init();
            c->SetResource(this);
        }
    };
    virtual void Uninit() {
        for (Component* c : Components) {
            c->Uninit();
        }
    };
    virtual void Update() {
        for (Component* c : Components) {
            c->Update();
        }
    };
    virtual void FixedUpdate() {
        for (Component* c : Components) {
            c->FixedUpdate();
        }
    };

    virtual void Render() {};

    // �폜
    void Destroy() { this->Alive = false; };
    // �폜�i�����p�j
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

    // Setter
    void SetActive(bool active) { this->Active = active; };

    // Getter
    bool GetActive() { return this->Active; };
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

    // ��]�i��]���w��j
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
        /*Component->SetResource(this);*/
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
        return nullptr;
    };

};