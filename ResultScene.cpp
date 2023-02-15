#include "ResultScene.h"
#include"Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "UDPServer.h"

int ResultScene::mode;

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene"), hPict_()
{
}
//������
void ResultScene::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_[0] = Image::Load("youWin.jpg");
    assert(hPict_[0] >= 0);

	//�摜�f�[�^�̃��[�h
	hPict_[1] = Image::Load("youLose.jpg");
	assert(hPict_[1] >= 0);
}

//�X�V
void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//�`��
void ResultScene::Draw()
{
	//��������
	if (!UDPServer::GetIsLose())
	{
		Image::SetTransform(hPict_[0], transform_);
		Image::Draw(hPict_[0]);
	}
	else
	{
		Image::SetTransform(hPict_[1], transform_);
		Image::Draw(hPict_[1]);
	}
}

//�J��
void ResultScene::Release()
{
}

