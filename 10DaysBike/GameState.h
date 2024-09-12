#pragma once
#include "ScoreManager.h"
#include <memory>

class GameState
{
public:

    void Init();
    void Update();
    void Draw();

public:
    
    // シーン間での共有データ
    //スコアマネージャー
    std::unique_ptr<ScoreManager> scoreManager_;
};

