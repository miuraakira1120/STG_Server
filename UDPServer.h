#pragma once
 

//���������Ǘ�����N���X
namespace UDPServer
{
    //������
    void Initialize();

    //�X�V
    void Update();

    //�Q�b�^�[
    float GetMoveX();
    bool GetEnemyShotFlag();
    bool GetIsStart();
    bool GetIsLose();

    //�Z�b�^�[
    void SetMoveX(float posX);
    void SetPlayerShotFlag(bool bullet);
    void SetIsLose();
    void SetIsStart(bool startFlag);
};