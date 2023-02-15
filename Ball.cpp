#include "Ball.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Enemy.h"
#include "Player.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball")
{
    hModel_ = -1;
    bulletType = -1;
}

//�f�X�g���N�^
Ball::~Ball()
{
}

//������
void Ball::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("WhiteBall.fbx");
    assert(hModel_ >= 0);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.2);
    AddCollider(collision);
}

//�X�V
void Ball::Update()
{
    //�f�o�b�O�p
    if (Input::IsKey(DIK_B))
    {
        int a = 0;
    }

    bulletType == 0 ? transform_.position_.z += 0.1
                    : transform_.position_.z -= 0.1;


    if (transform_.position_.z >= 15 || transform_.position_.z <= -15)
    {
        KillMe();
    }
}

//�`��
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Ball::Release()
{
    
}

//�����蔻��
void Ball::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Player" && bulletType == 1)
    {
        //pTarget->KillMe();
        //damage++;
        Player* pPlayer = (Player*)FindObject("Player");
        pPlayer->Damage(1);
        //if (damage >= HP)
        {
            KillMe();
        }
    }

    if (pTarget->GetObjectName() == "Enemy" && bulletType == 0)
    {
        //pTarget->KillMe();
        //damage++;
        Enemy* pEnemy = (Enemy*)FindObject("Enemy");
        pEnemy->Damage(1);
        //if (damage >= HP)
        {
            KillMe();
        }
    }
}

int Ball::GetBulletType()
{
    return bulletType;
}

void Ball::SetBulletType(int type)
{
    bulletType = type;
}




