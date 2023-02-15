#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"
#include "UDPServer.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player")
{

}

//デストラクタ
Player::~Player()
{

}

//初期化
void Player::Initialize()
{
    hModel_ = Model::Load("PlayerBone.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = -7;
    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    AddCollider(collision);

    damage = 0;
}

//更新
void Player::Update()
{
    //+-13
    XMFLOAT3 LeftStick = Input::GetPadStickL();
    LeftStick.x /= 10;
    /*transform_.position_.x += LeftStick.x;
    transform_.position_.z += LeftStick.y;*/

    XMFLOAT3 move = { LeftStick.x,0,0 }; //移動量
    XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
    //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

    //vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

    vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

    XMStoreFloat3(&transform_.position_, vPos);


    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
    {
        //Instantiate<bullet>(GetParent());//()の中は親
        pBall = Instantiate<Ball>(GetParent());
        //親からハート発射
        pBall->SetPosition(transform_.position_);
    }

    //D押したら右
    if (Input::IsKey(DIK_D))
    {
        if (transform_.position_.x < MAX_X)
        {
            XMFLOAT3 move = { PLAYER_MOVE,0,0 }; //移動量
            XMVECTOR vMove = XMLoadFloat3(&move); //移動量をベクトルに変換 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸でｙ°回転させる行列

            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //現在地をベクトルに変換

            vPos += vMove; //現在の位置ベクトルに移動量ベクトルを足す

            XMStoreFloat3(&transform_.position_, vPos);
        }
    }
    //A押したら
    if (Input::IsKey(DIK_A))
    {
        if (transform_.position_.x > -MAX_X)
        {
            XMFLOAT3 move = { -PLAYER_MOVE,0,0 }; //
            XMVECTOR vMove = XMLoadFloat3(&move); //
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y軸で90°回転させる行列
            vMove = XMVector3TransformCoord(vMove, mRotate);	//ベクトルｖを行列ｍで変形
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //

            vPos += vMove;

            XMStoreFloat3(&transform_.position_, vPos);
        }
    }

    if (Input::IsKeyDown(DIK_SPACE))
    {
        Ball* pBall =  Instantiate<Ball>(GetParent());
        pBall->SetBulletType(0);//0はプレイヤー、1は敵
        pBall->SetPosition(transform_.position_);
        UDPServer::SetPlayerShotFlag(true);
    }
    else
    {
        UDPServer::SetPlayerShotFlag(false);
    }
    UDPServer::SetMoveX(transform_.position_.x);

    //デバッグ用
    if (Input::IsKeyDown(DIK_B))
    {
        int a = 0;
    }

    //transform_.position_.x = UDPServer::GetMoveX();
}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Player::Release()
{
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
}


void Player::Damage(int damage_)
{
    damage += damage_;

    if (damage >= HP)
    {
        UDPServer::SetIsLose();
        KillMe();
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_RESULT);
    }
}
