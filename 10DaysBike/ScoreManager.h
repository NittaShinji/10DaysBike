#pragma once
#include "Score.h"
#include <memory>

class ScoreManager
{
public:

	void Init();
	void Update();
	void Draw();

	void UpdateRanking();

private:

	std::unique_ptr<Score> totalScore_ = nullptr;

	//�����L���O�摜
	int32_t rankingHandle_;
	//�X�R�A�摜
	int32_t scoreHandle_;
};

