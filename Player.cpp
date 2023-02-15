#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include"Ball.h"
#include "Engine/SphereCollider.h"
#include "UDPServer.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player")
{

}

//�f�X�g���N�^
Player::~Player()
{

}

//������
void Player::Initialize()
{
    hModel_ = Model::Load("PlayerBone.fbx");
    assert(hModel_ >= 0);

    transform_.position_.z = -7;
    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    AddCollider(collision);

    damage = 0;
}

//�X�V
void Player::Update()
{
    //+-13
    XMFLOAT3 LeftStick = Input::GetPadStickL();
    LeftStick.x /= 10;
    /*transform_.position_.x += LeftStick.x;
    transform_.position_.z += LeftStick.y;*/

    XMFLOAT3 move = { LeftStick.x,0,0 }; //�ړ���
    XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
    //XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

    //vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

    vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

    XMStoreFloat3(&transform_.position_, vPos);


    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
    {
        //Instantiate<bullet>(GetParent());//()�̒��͐e
        pBall = Instantiate<Ball>(GetParent());
        //�e����n�[�g����
        pBall->SetPosition(transform_.position_);
    }

    //D��������E
    if (Input::IsKey(DIK_D))
    {
        if (transform_.position_.x < MAX_X)
        {
            XMFLOAT3 move = { PLAYER_MOVE,0,0 }; //�ړ���
            XMVECTOR vMove = XMLoadFloat3(&move); //�ړ��ʂ��x�N�g���ɕϊ� 
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y���ł�����]������s��

            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���ݒn���x�N�g���ɕϊ�

            vPos += vMove; //���݂̈ʒu�x�N�g���Ɉړ��ʃx�N�g���𑫂�

            XMStoreFloat3(&transform_.position_, vPos);
        }
    }
    //A��������
    if (Input::IsKey(DIK_A))
    {
        if (transform_.position_.x > -MAX_X)
        {
            XMFLOAT3 move = { -PLAYER_MOVE,0,0 }; //
            XMVECTOR vMove = XMLoadFloat3(&move); //
            XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));   //Y����90����]������s��
            vMove = XMVector3TransformCoord(vMove, mRotate);	//�x�N�g�������s�񂍂ŕό`
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //

            vPos += vMove;

            XMStoreFloat3(&transform_.position_, vPos);
        }
    }

    if (Input::IsKeyDown(DIK_SPACE))
    {
        Ball* pBall =  Instantiate<Ball>(GetParent());
        pBall->SetBulletType(0);//0�̓v���C���[�A1�͓G
        pBall->SetPosition(transform_.position_);
        UDPServer::SetPlayerShotFlag(true);
    }
    else
    {
        UDPServer::SetPlayerShotFlag(false);
    }
    UDPServer::SetMoveX(transform_.position_.x);

    //�f�o�b�O�p
    if (Input::IsKeyDown(DIK_B))
    {
        int a = 0;
    }

    //transform_.position_.x = UDPServer::GetMoveX();
}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Player::Release()
{
}

//�����ɓ�������
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
