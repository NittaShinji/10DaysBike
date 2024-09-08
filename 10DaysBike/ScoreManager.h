#pragma once
#include "Score.h"
#include <vector>
#include <memory>

class ScoreManager
{
public:
	void Init();
	void Update(int enemyDeadNum);
	void Draw();

private:

	const int kRankNum = 5;
	std::vector<std::unique_ptr<Score>> bullets_;

public:

};

