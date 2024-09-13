#pragma once
#include "Score.h"
#include "dxlib.h"
#include <memory>
#include <vector>
#include <string>

class ScoreManager
{
public:

	static const int kGameClearScore = 600;

public:

	void Init();
	void Update();
	void Draw();
	void Reset();

	void ResetInit();
	void ResetUpdate();
	void ResetDraw();

	void RegistScore(std::vector<std::string>& deadEnemyNames);

	void InitRanking();
	void UpdateRanking();
	void RegistRanking();
	void DrawRanking();

private:

	std::unique_ptr<Score> totalScore_ = nullptr;
	std::unique_ptr<Score> resultScore_ = nullptr;

	std::unique_ptr<Score> goldScore_ = nullptr;
	std::unique_ptr<Score> silberScore_ = nullptr;
	std::unique_ptr<Score> bronzeScore_ = nullptr;

	//ランキング画像
	int32_t rankingHandle_;
	//スコア画像
	int32_t scoreHandle_;

	const int kRankNum = 5;
	int ranking[500] = { 0 };
	bool isLoggedIn = false;
	bool isConnectingToAPI = false;
	bool isRegistRanking_ = false;
	std::wstring token;
	const unsigned int stringCr = GetColor(255, 255, 255);

public:

	Score* GetTotalScore() { return totalScore_.get(); }
	Score* GetResultScore() { return resultScore_.get(); }
	void SetIsRegistRanking(bool isRegistRanking) { isRegistRanking_ = isRegistRanking; }
};

