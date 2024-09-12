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
	void Pop();
	void Draw();
	int GetScore() { return score_; }

	//数値情報を桁数に入力
	//スコア入力
	void InputNumberTS();
	void InputDrumRoll();

	float EaseInOutExpo(float t, float b, float c, float d);

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
	//リザルトで足していくときのタイマー
	float drumTimer_ = 0;
	//ドラムロールする時間
	float kMaxDrumTime_ = 340;

	//ドラムロールしているかのフラグ
	bool isDrumRoll_ = false;
};

