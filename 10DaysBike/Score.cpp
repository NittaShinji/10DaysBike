#include "Score.h"
#include "Easing.h"
#include "DxLib.h"
#include "Inform.h"
#include "KeyboardInput.h"
#include <cassert>

int Score::textureHandle_[kScoreNumberNum_];

Score::~Score()
{
	// 読み込んだ画像のグラフィックハンドルを削除
	for (int i = 0; i < kScoreNumberNum_; i++)
	{
		DeleteGraph(textureHandle_[i]);
	}
}

void Score::Load()
{
	//テクスチャ読み込み
	LoadDivGraph((RESOUCE_PATH + "bitmap_num.png").c_str(), 10, 10, 1, 32, 32, textureHandle_);
}

void Score::Init(Vec2 pos)
{
	//得点初期化
	score_ = 0;
	isDrumRoll_ = false;

	//どれぐらいの等間隔で離すか
	const float equalDistanceX = 48.0f;
	const float equalDistanceY = 0.0f;

	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		// 座標の初期化
		pos_[i] = Vec2((i * equalDistanceX) + 16.0f, 10.0f);
	}
}

void Score::Update()
{
	if (isDrumRoll_)
    {
        InputDrumRoll();

        // ドラムロールスコアが目標スコアに達したら終了
        if (drumRollscore_ >= targetScore_) {
            isDrumRoll_ = false;
            drumRollscore_ = targetScore_;  // 最終的なスコアに合わせる
			score_ = targetScore_;
        }
    }
    else
    {
        InputNumberTS();  // 通常のスコア表示
    }
}

void Score::Draw()
{
	//0～9までそれぞれ描画
	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		DrawRotaGraph(pos_[i].x + 56, pos_[i].y + 60, 2.0f, 0, textureHandle_[displayNum_[i]], TRUE);
	}
}

void Score::SetPos(Vec2 pos)
{
	//どれぐらいの等間隔で離すか
	const float equalDistanceX = 48.0f;
	const float equalDistanceY = 0.0f;

	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		// 座標の初期化
		pos_[i] = Vec2((i * equalDistanceX) + pos.x, pos.y);
	}
}

void Score::InputNumberTS()
{
	//--7桁目(10万の位を表示)
	displayNum_[0] = (score_ % 10000000) / 1000000;
	//--6桁目(万の位を表示)
	displayNum_[1] = (score_ % 1000000) / 100000;
	//--5桁目(千の位を表示)
	displayNum_[2] = (score_ % 100000) / 10000;
	//--4桁目(百の位を表示)
	displayNum_[3] = (score_ % 10000) / 1000;
	//--3桁目(十の位を表示)
	displayNum_[4] = (score_ % 1000) / 100;
	//--2桁目(1の位を表示)
	displayNum_[5] = (score_ % 100) / 10;
	//--1桁目(1の位を表示)
	displayNum_[6] = (score_ % 10) / 1;
}

void Score::InputDrumRoll()
{
	//t 経過時間	b最初の位置	c移動量	d移動時間
	if (isDrumRoll_)
	{
		if (drumTimer_ < kMaxDrumTime_)
		{
			drumTimer_++;
		}

		// ドラムロールの表示スコアを更新（スコアの変動に対応）
		drumRollscore_ = EaseOutSine(drumTimer_, drumRollscore_, static_cast<float>(targetScore_ - drumRollscore_), kMaxDrumTime_);
	}

	//drumRollscore_ = EaseInOutExpo(drumTimer_, 0.0f, static_cast<float>(score_), kMaxDrumTime_);
	//drumRollscore_ = EaseOutSine(drumTimer_, 0.0f, static_cast<float>(score_), kMaxDrumTime_);


	//--7桁目(10万の位を表示)
	displayNum_[0] = (drumRollscore_ % 10000000) / 1000000;
	//--6桁目(万の位を表示)
	displayNum_[1] = (drumRollscore_ % 1000000) / 100000;
	//--5桁目(千の位を表示)
	displayNum_[2] = (drumRollscore_ % 100000) / 10000;
	//--4桁目(百の位を表示)
	displayNum_[3] = (drumRollscore_ % 10000) / 1000;
	//--3桁目(十の位を表示)
	displayNum_[4] = (drumRollscore_ % 1000) / 100;
	//--2桁目(1の位を表示)
	displayNum_[5] = (drumRollscore_ % 100) / 10;
	//--1桁目(1の位を表示)
	displayNum_[6] = (drumRollscore_ % 10) / 1;
}

void Score::SetEqualDistancePos(Vec2 distancePos)
{
	//どれぐらいの等間隔で離すか
	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		// 座標の初期化
		pos_[i] = Vec2((i * distancePos.x) + 16.0f, 10.0f);
	}
}

float Score::EaseInOutExpo(float t, float b, float c, float d) {
	if (t == 0) return b;
	if (t == d) return b + c;
	if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
	return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

float Score::EaseOutSine(float t, float b, float c, float d)
{
	float x = t / d;
	return c * sin((x * 3.1415) / 2) + b;
}

void Score::StartDrumRoll(int32_t newScore)
{
	if (isDrumRoll_)
	{
		// 既存のドラムロールの目標スコアを更新
		targetScore_ = newScore;
	}
	else
	{
		// ドラムロールを開始
		score_ += newScore; // 既存のスコアに追加
		targetScore_ = score_; // 新しい目標スコアに設定
		drumTimer_ = 0.0f; // タイマーをリセット
		isDrumRoll_ = true; // ドラムロールを有効にする
	}
}

void Score::Reset()
{
	//加算するスコア
	score_ = 0;

	//ドラムロールするスコア
	drumRollscore_ = 0;
	//目標スコア
	targetScore_ = 0;
	//リザルトで足していくときのタイマー
	drumTimer_ = 0;

	//ドラムロールしているかのフラグ
	isDrumRoll_ = false;

	//ドラムロールの目標スコア
	drumRollscoreTarget_ = 0;

	isDrumRoll_ = false;

	//ドラムロールの目標スコア
	drumRollscoreTarget_ = 0;

	//どれぐらい離すか
	const float equalDistanceX = 48.0f;
	const float equalDistanceY = 0.0f;

	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		// 座標の初期化
		pos_[i] = Vec2((i * equalDistanceX) + 16.0f, 10.0f);
	}
}
