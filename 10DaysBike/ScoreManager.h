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

	//�����L���O�摜
	int32_t rankingHandle_;
	//�X�R�A�摜
	int32_t scoreHandle_;
};

