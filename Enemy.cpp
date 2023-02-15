#include "Enemy.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"

#include "UDPServer.h"
#include "Engine/SceneManager.h"


//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy")
{

}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化
void Enemy::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = 5;
    transform_.rotate_.y = 180;
    damage = 0;

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    AddCollider(collision);
}

//更新
void Enemy::Update()
{
    if (UDPServer::GetEnemyShotFlag())
    {
        Ball* pBall = Instantiate<Ball>(GetParent());
        pBall->SetBulletType(1);//0はプレイヤー、1は敵
        pBall->SetPosition(transform_.position_);
    }
    transform_.position_.x = UDPServer::GetMoveX();
}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Enemy::Release()
{
}

//何かに当たった
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

