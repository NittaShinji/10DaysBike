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

	//ランキング画像
	int32_t rankingHandle_;
	//スコア画像
	int32_t scoreHandle_;
};

