#pragma once
#include "ScoreManager.h"
#include <memory>

class GameState
{
public:

    void Init();
    void Update();
    void Draw();

    void SetIsClear(bool isClear) { isClear_ = isClear; }
    bool GetIsClear() { return isClear_; }

public:
    
    // シーン間での共有データ
    //スコアマネージャー
    std::unique_ptr<ScoreManager> scoreManager_;

    //ゲームをクリアしたかどうか
    bool isClear_ = false;
};

