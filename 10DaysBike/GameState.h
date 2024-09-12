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
    
    // �V�[���Ԃł̋��L�f�[�^
    //�X�R�A�}�l�[�W���[
    std::unique_ptr<ScoreManager> scoreManager_;

    //�Q�[�����N���A�������ǂ���
    bool isClear_ = false;
};

