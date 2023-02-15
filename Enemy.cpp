#include "Enemy.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"

#include "UDPServer.h"
#include "Engine/SceneManager.h"


//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy")
{

}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//������
void Enemy::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = 5;
    transform_.rotate_.y = 180;
    damage = 0;

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    AddCollider(collision);
}

//�X�V
void Enemy::Update()
{
    if (UDPServer::GetEnemyShotFlag())
    {
        Ball* pBall = Instantiate<Ball>(GetParent());
        pBall->SetBulletType(1);//0�̓v���C���[�A1�͓G
        pBall->SetPosition(transform_.position_);
    }
    transform_.position_.x = UDPServer::GetMoveX();
}

//�`��
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Enemy::Release()
{
}

//�����ɓ�������
void Enemy::OnCollision(GameObject* pTarget)
{

    /*if (pTarget->GetObjectName() == "Ball")
    {
        pTarget->KillMe();
        damage++;

        if (damage >= HP)
        {

            KillMe();
        }
    }*/

}

void Enemy::Damage(int damage_)
{
     damage += damage_;

     if (damage >= HP)
     {

         KillMe();
         SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
         pSceneManager->ChangeScene(SCENE_ID_RESULT);
     }
}

