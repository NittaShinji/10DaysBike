#include "DxLib.h" 
#include "Inform.h" 
#include "KeyboardInput.h" 
#include "Player.h" 
#include "PlayerState.h" 
#include "Enemy.h" 
#include "EnemyState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EnergyGauge.h"

// ウィンドウのタイトルに表示する文字列

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE.c_str());

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	auto player = std::make_unique<Player>();
	player->Init({ WINDOW_SIZE.x / 2,WINDOW_SIZE.y / 2 });

	auto gauge = std::make_unique<EnergyGauge>();
	gauge->Init();

	std::unique_ptr <EnemyManager> enemyManager = std::make_unique<EnemyManager>();
	enemyManager->Init();

	//衝突マネージャー
	CollisionManager* collisionManager_ = nullptr;
	collisionManager_ = CollisionManager::GetInstance();

	// ゲームループ
	while (true) {

		KeyboardInput::GetInstance().Update();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		player->Update([&](float shootGaugeDecre) { return gauge->DecreGaugeRatio(shootGaugeDecre); },
			[&](float posY, float shootChargeGauge) { return gauge->ChargeGaugeRatio(posY, shootChargeGauge); },
			gauge->FRAME_TOP);
		enemyManager->Update();
		gauge->Update();

		//全ての衝突をチェック
		collisionManager_->CheckAllCollisions();

		// 描画処理
		player->Draw();
		enemyManager->Draw();
		gauge->Draw();

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
