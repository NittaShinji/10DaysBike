#pragma once
#include "Score.h"
#include <memory>
#include <vector>
#include <string>

class ScoreManager
{
public:

	static const int kGameClearScore = 100;

public:

	void Init();
	void Update();
	void Draw();
	void Reset();

	void RegistScore(std::vector<std::string>& deadEnemyNames);

	void UpdateRanking();

private:

	std::unique_ptr<Score> totalScore_ = nullptr;

	//ランキング画像
	int32_t rankingHandle_;
	//スコア画像
	int32_t scoreHandle_;

public:

	Score* GetTotalScore() { return totalScore_.get(); }
};

