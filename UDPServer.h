#pragma once
 

//◆◆◆を管理するクラス
namespace UDPServer
{
    //初期化
    void Initialize();

    //更新
    void Update();

    //ゲッター
    float GetMoveX();
    bool GetEnemyShotFlag();
    bool GetIsStart();
    bool GetIsLose();

    //セッター
    void SetMoveX(float posX);
    void SetPlayerShotFlag(bool bullet);
    void SetIsLose();
    void SetIsStart(bool startFlag);
};