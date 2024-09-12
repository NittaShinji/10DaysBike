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
	LoadDivGraph((RESOUCE_PATH + "number.png").c_str(), 10, 10, 1, 32, 32, textureHandle_);
}

void Score::Init(Vec2 pos)
{
	//得点初期化
	score_ = 1023459;
	isDrumRoll_ = false;

	//どれぐらいの等間隔で離すか
	const float equalDistanceX = 32.0f;
	const float equalDistanceY = 0.0f;

	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		// 座標の初期化
		pos_[i] = Vec2((i * equalDistanceX), 10.0f);
	}
}

void Score::Update()
{
	//敵が死んだ際に敵の種類によってポイントを変える

	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_T)) {
		//ゲームシーンに移動
		isDrumRoll_ = true;
	}

	if (isDrumRoll_ == true)
	{
		InputDrumRoll();
	}

}

void Score::Draw()
{
	//0〜9までそれぞれ描画
	for (int i = 0; i < kScoreDigitNum_; i++)
	{
		DrawGraph(pos_[i].x + UI_SIZE.x, pos_[i].y, textureHandle_[displayNum_[i]], true);
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
	if (drumTimer_ < kMaxDrumTime_) 
	{
		drumTimer_++;
	}
	else
	{
		isDrumRoll_ = false;
	}

	drumRollscore_ = EaseInOutExpo(drumTimer_, 0.0f, static_cast<float>(score_), kMaxDrumTime_);

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

float Score::EaseInOutExpo(float t, float b, float c, float d) {
	if (t == 0) return b;
	if (t == d) return b + c;
	if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
	return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}
