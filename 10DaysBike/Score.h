#pragma once
#include "Vec2.h"
class Score
{
public:

	static const int kScoreDigitNum_ = 7;
	static const int kScoreNumberNum_ = 10;

public:
	~Score();
	static void Load();
	void Init(Vec2 pos);
	void Update();
	void Draw();
	int GetScore() { return score_; }
	int GetTargetScore() { return targetScore_; }
	bool GetIsDrum() { return isDrumRoll_; }

	void SetIsDrum(bool isDrumRoll) { isDrumRoll_ = isDrumRoll; }
	void SetDrumTimer(float drumRollTimer) { drumTimer_ = drumRollTimer; }
	void SetTargetScore(int targetScore) { targetScore_ = targetScore; }

	//スコア追加
	void AddScore(int32_t addNum)
	{
		//if (isDrumRoll_)
		//{
		//	// ドラムロール中の場合、追加のスコアはドラムロールの目標スコアに反映
		//	drumRollscoreTarget_ += addNum;
		//}
		//else
		//{
		//	score_ += addNum;
		//}

		score_ += addNum;
	};

	//数値情報を桁数に入力
	//スコア入力
	void InputNumberTS();
	void InputDrumRoll();

	float EaseInOutExpo(float t, float b, float c, float d);
	float EaseOutSine(float t, float b, float c, float d);

	void StartDrumRoll(int32_t newScore); // ドラムロールを開始する新しい関数を追加

	void Reset();

private:

	//二次元用の座標
	Vec2 pos_[kScoreDigitNum_];
	int popPos_ = 0;
	int popVec_ = 0;

	//表示するスコア画像用の変数(表示桁数)
	int displayNum_[kScoreDigitNum_];
	//数字の画像用ハンドル
	static int textureHandle_[kScoreNumberNum_];

	//基本得点
	const int scoreNum = 100;
	//加算するスコア
	int score_ = 0;

	//ドラムロールするスコア
	int drumRollscore_ = 0;
	//目標スコア
	int targetScore_ = 0;
	//リザルトで足していくときのタイマー
	float drumTimer_ = 0;
	//ドラムロールする時間
	const float kMaxDrumTime_ = 90;

	//ドラムロールしているかのフラグ
	bool isDrumRoll_ = false;

	//ドラムロールの目標スコア
	int drumRollscoreTarget_ = 0;
};