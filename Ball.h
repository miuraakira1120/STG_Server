#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"
#include "Engine/Fbx.h"
#include "Ball.h"

//���������Ǘ�����N���X
class Ball : public GameObject
{
    int hModel_;    //���f���ԍ�
    int bulletType;

public:
    int ballID;
    //�R���X�g���N�^
    Ball(GameObject* parent);

    //�f�X�g���N�^
    ~Ball();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    //�Q�b�^�[
    int GetBulletType();

    //�Z�b�^�[
    void SetBulletType(int type);
};