#pragma once
#include "Score.h"
#include <memory>
#include <vector>
#include <string>

class ScoreManager
{
public:

	static const int kGameClearScore = 5200;

public:

	void Init();
	void Update();
	void Draw();
	void Reset();

	void ResetInit();
	void ResetUpdate();
	void ResetDraw();

	void RegistScore(std::vector<std::string>& deadEnemyNames);

	void UpdateRanking();

private:

	std::unique_ptr<Score> totalScore_ = nullptr;
	std::unique_ptr<Score> resultScore_ = nullptr;

	//ランキング画像
	int32_t rankingHandle_;
	//スコア画像
	int32_t scoreHandle_;

public:

	Score* GetTotalScore() { return totalScore_.get(); }
	Score* GetResultScore() { return resultScore_.get(); }
};

