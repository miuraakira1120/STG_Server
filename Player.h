#pragma once
#include "Engine/GameObject.h"
#include "Ball.h"

//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�

    const int HP = 3;
    const float RETURN_MOVE = 0.01f;
    const float PLAYER_MOVE = 0.1f;//�ړ�����
    const float MAX_X = 15;

    int damage;
    Ball* pBall = (Ball*)FindObject("Ball");
public:
    int playerID;

    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

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