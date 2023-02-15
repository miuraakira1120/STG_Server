#pragma once
#include "Engine/GameObject.h"
#include "Ball.h"

//���������Ǘ�����N���X
class Enemy : public GameObject
{
    int hModel_;    //���f���ԍ�

    const int HP = 3;
    const float RETURN_MOVE = 0.01f;
    const float Enemy_MOVE = 0.1f;//�ړ�����

    int damage;
    Ball* pBall = (Ball*)FindObject("Ball");
public:
    int EnemyID;

    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

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

    void Damage(int damage);
};