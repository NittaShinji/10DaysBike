#pragma once
#include "BaseScene.h"
#include "Player.h" 
#include "PlayerState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EnergyGauge.h"
#include "BackGround.h"
#include "Score.h"
#include "Easing.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public BaseScene
{
public:

	//静的初期化
	static void StaticInitialize();

	//リソース削除
	static void DeleteResource();

	//初期化
	void Initialize() override;

	//毎フレーム更新
	void Update() override;

	//描画
	void Draw() override;

private:

	//ブルーム
	int ColorScreen;	// 普通の描画結果を書き込むスクリーン
	int HighBrightScreen;	// 普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
	int DownScaleScreen;	// 高輝度部分を縮小した結果を書き込むスクリーン
	int GaussScreen;	// 縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン
	int Angle;		// カメラの水平角度
	int StageModel;	// ステージモデル
	int GaussRatio;	// ガウスフィルタのぼかし度合い

	// ゲームループで使う変数の宣言
	std::unique_ptr <Player> player = nullptr;
	std::unique_ptr <EnergyGauge> gauge = nullptr;
	std::unique_ptr <EnemyManager> enemyManager = nullptr;
	std::unique_ptr <Score> score_ = nullptr;

	//衝突マネージャー
	static CollisionManager* collisionManager_;
	//背景クラス
	std::unique_ptr <BackGround> backGround = nullptr;

	//ゲーム内BGM
	static int bgmHandle_;
	//スタート音
	static int startHandle_;
	//UI画像
	static int uiHandle_;
	//Finish画像
	static int finishHandle_;
	//説明画像
	static int explainHandle_;

	const Vec2 kDefaultPos_ = { 14 + UI_SIZE.x,-150};
	const Vec2 kDropPos_ = { 0,300 };

	Vec2 finishPos_;

	bool isStartFinishAnime_ = false;

	const float kEasingTime_ = 60.0f;
	EasingInfo resultOutEasing_ = { 0.0f, 300.0f, 0.0f, kEasingTime_ };

	const float kWaitTime_ = 90.0f;
	float waitTime_ = kWaitTime_;

	const float kExplainTime_ = 165.0f;
	float explainTime_ = kWaitTime_;

	bool isStart_ = false;
};

