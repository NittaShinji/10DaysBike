#include "GameScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"

// スクリーン変数
#define SCREEN_W		WINDOW_SIZE.x				// 画面の横幅
#define SCREEN_H		WINDOW_SIZE.y				// 画面の縦幅
#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
#define DOWN_SCALE_SCREEN_W	( SCREEN_W / DOWN_SCALE )	// ガウスフィルタを掛ける画像の横幅
#define DOWN_SCALE_SCREEN_H	( SCREEN_H / DOWN_SCALE )	// ガウスフィルタを掛ける画像の縦幅

CollisionManager* GameScene::collisionManager_ = nullptr;

void GameScene::StaticInitialize()
{
	collisionManager_ = CollisionManager::GetInstance();
	Score::Load();
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
	enemyManager->Init();
	enemyManager->SetPlayerPosPtr(player->GetPlayerPosPtr());
	backGround->Init();
	score_ = std::make_unique<Score>();
	score_->Init(Vec2(40,400));
}

void GameScene::Update()
{
	// 更新処理
	player->Update([&](float shootGaugeDecre) { return gauge->DecreGaugeRatio(shootGaugeDecre); },
		[&](float posY, float shootChargeGauge) { return gauge->ChargeGaugeRatio(posY, shootChargeGauge); },
		gauge->FRAME_TOP);
	enemyManager->Update();
	gauge->Update();
	backGround->Update(player->GetVec().y, player->GetPlayerState());
	score_->Update();

	//全ての衝突をチェック
	collisionManager_->CheckAllCollisions(player->GetPos(), 30.0f);


	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
		//クリアシーンに移動
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}
	else if (! player->GetIsAlive()) {
		//タイトルシーンに移動
		SceneManager::GetInstance()->ChangeScene("TITLE");
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
	enemyManager->Draw();
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
	score_->Draw();
	gauge->Draw();
}
