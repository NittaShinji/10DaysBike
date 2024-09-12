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
    
    // �V�[���Ԃł̋��L�f�[�^
    //�X�R�A�}�l�[�W���[
    std::unique_ptr<ScoreManager> scoreManager_;
};

