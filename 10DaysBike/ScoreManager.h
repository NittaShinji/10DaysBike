#pragma once
#include "Score.h"
#include <memory>
#include <vector>
#include <string>

class ScoreManager
{
public:

	struct EnemyRegistInfo
	{
		std::string name;
		bool isRegist;
	};


public:

	void Init();
	void Update();
	void Draw();

	void RegistScore(std::vector<std::string>& deadEnemyNames);

	void UpdateRanking();

private:

	std::unique_ptr<Score> totalScore_ = nullptr;

	//ランキング画像
	int32_t rankingHandle_;
	//スコア画像
	int32_t scoreHandle_;
};

