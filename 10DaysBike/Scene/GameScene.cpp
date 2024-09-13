#include "GameScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"
#include "ParticleEffectManager.h"

// スクリーン変数
#define SCREEN_W		WINDOW_SIZE.x				// 画面の横幅
#define SCREEN_H		WINDOW_SIZE.y				// 画面の縦幅
#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
#define DOWN_SCALE_SCREEN_W	( SCREEN_W / DOWN_SCALE )	// ガウスフィルタを掛ける画像の横幅
#define DOWN_SCALE_SCREEN_H	( SCREEN_H / DOWN_SCALE )	// ガウスフィルタを掛ける画像の縦幅

CollisionManager* GameScene::collisionManager_ = nullptr;
int GameScene::bgmHandle_;
int GameScene::startHandle_;
int GameScene::uiHandle_;

void GameScene::StaticInitialize()
{
	collisionManager_ = CollisionManager::GetInstance();
	bgmHandle_ = LoadSoundMem((RESOUCE_PATH + "gameBGM.wav").c_str());
	startHandle_ = LoadSoundMem((RESOUCE_PATH + "gameStart.wav").c_str());
	uiHandle_ = LoadGraph((RESOUCE_PATH + "UI.png").c_str());

	IEnemy::LoadSound();
}

void GameScene::DeleteResource()
{
	IEnemy::UnloadSound();
	DeleteSoundMem(bgmHandle_);
	DeleteSoundMem(startHandle_);
	DeleteSoundMem(uiHandle_);
}

void GameScene::Initialize()
{
	//登録していたコライダーを全て削除(オブジェクトの初期化前に行う(初期化時にコライダーを追加するため))
	collisionManager_->RemoveCollider();

	// 画像などのリソースデータの変数宣言と読み込み
	// 通常の描画結果を書き込むスクリーンと、フィルターの処理結果を書き込むスクリーンの作成
	ColorScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	HighBrightScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	DownScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	GaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	// カメラの角度とガウスフィルタのぼかし度合いを初期化
	Angle = 0;
	GaussRatio = 900;

	//初期化
	player = std::make_unique<Player>();
	gauge = std::make_unique<EnergyGauge>();
	enemyManager = std::make_unique<EnemyManager>();
	backGround = std::make_unique<BackGround>();

	player->Init({ UI_SIZE.x + WINDOW_SIZE.x / 2,WINDOW_SIZE.y / 2 });
	player->SetDamagedFunc([&](float decreGaugeRatio) { return gauge->DamageDecreGauge(decreGaugeRatio); });
	gauge->Init();
	enemyManager->Init([&](float chargeRatio) { gauge->ChargeGaugeRatio(chargeRatio); });
	enemyManager->SetPlayerPosPtr(player->GetPlayerPosPtr());
	backGround->Init();
	// 音量の設定
	ChangeVolumeSoundMem(255 * 50 / 100, startHandle_);
	//BGM再生
	PlaySoundMem(startHandle_, DX_PLAYTYPE_BACK);

	ParticleEffectManager::GetInstance().Init();
}

void GameScene::Update()
{
	if (CheckSoundMem(startHandle_) == 0 && isStart_ == false)
	{
		// 音量の設定
		ChangeVolumeSoundMem(255 * 50 / 100, bgmHandle_);
		//BGM再生
		PlaySoundMem(bgmHandle_, DX_PLAYTYPE_LOOP);
		isStart_ = true;
	}

	// 更新処理
	player->Update([&](float shootGaugeDecre, int32_t continueNum) { return gauge->DecreGaugeRatio(shootGaugeDecre, continueNum); },
		[&](float posY, float shootChargeGauge) { return gauge->ChargeGaugeRatio(posY, shootChargeGauge); },
		gauge->FRAME_TOP);
	if (isStart_ == true)
	{
		enemyManager->Update();
	}

	gauge->Update();
	backGround->Update(player->GetVec().y, player->GetPlayerState());
	gameState_->scoreManager_->RegistScore(enemyManager->GetDeadEnemyNames());
	gameState_->scoreManager_->Update();

	//全ての衝突をチェック
	collisionManager_->CheckAllCollisions(player->GetPos(), 30.0f);

	ParticleEffectManager::GetInstance().Update();

	if (! player->GetIsAlive()) {
		//ゲームオーバーシーンに移動
		SceneManager::GetInstance()->ChangeScene("RESULT");
		StopSoundMem(bgmHandle_);
		gameState_->SetIsClear(false);
	}
	else if (/*gameState_->scoreManager_->GetTotalScore()->GetScore() > ScoreManager::kGameClearScore ||*/ enemyManager->GetIsGameEnd() == true)
	{
		//クリアシーンに移動
		SceneManager::GetInstance()->ChangeScene("RESULT");
		StopSoundMem(bgmHandle_);
		gameState_->SetIsClear(true);
	}
}

void GameScene::Draw()
{
#pragma region ブルーム前処理
	// 通常の描画結果を書き込むスクリーンを描画対象にする
	SetDrawScreen(ColorScreen);

	// 画面をクリア
	ClearDrawScreen();

	// カメラの位置と向きを設定
	SetCameraPositionAndAngle(VGet(0.0f, 120.0f, 0.0f), 0.0f, Angle / 180.0f * 3.14159f, 0.0f);
#pragma endregion ブルーム前処理

	// ブルーム描画処理
	backGround->Draw();
	if (isStart_ == true)
	{
		enemyManager->Draw();
	}
	player->Draw();

#pragma region ブルーム後処理

	// 描画結果から高輝度部分のみを抜き出した画像を得る
	GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

	// 高輝度部分を８分の１に縮小した画像を得る
	GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

	// ８分の１に縮小した画像をガウスフィルタでぼかす
	GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);

	// 描画対象を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 通常の描画結果を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255); // アルファブレンドモードに設定
	DrawGraph(0, 0, ColorScreen, FALSE);

	// 描画モードをバイリニアフィルタリングにする( 拡大したときにドットがぼやけるようにする )
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// 描画ブレンドモードを加算にする
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// 高輝度部分を縮小してぼかした画像を画面いっぱいに２回描画する( ２回描画するのはより明るくみえるようにするため )
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);

	// 描画ブレンドモードをアルファブレンドに戻す
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// 描画モードを二アレストに戻す
	SetDrawMode(DX_DRAWMODE_NEAREST);

#pragma endregion ブルーム後処理

	//UI描画処理(ブルームなし)
	DrawGraph(0, 0, uiHandle_, true);
	gameState_->scoreManager_->Draw();
	gauge->Draw();

	ParticleEffectManager::GetInstance().Draw();
}
