#pragma once
#include "BaseScene.h"
#include "Player.h" 
#include "PlayerState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EnergyGauge.h"
#include "BackGround.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public BaseScene
{
public:

	//静的初期化
	static void StaticInitialize();

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
	
	//衝突マネージャー
	static CollisionManager* collisionManager_;
	//背景クラス
	std::unique_ptr <BackGround> backGround = nullptr;
};

