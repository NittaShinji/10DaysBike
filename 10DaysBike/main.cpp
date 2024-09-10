#include "DxLib.h" 
#include "Inform.h" 
#include "KeyboardInput.h" 
#include "Player.h" 
#include "PlayerState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EnergyGauge.h"

// スクリーン変数
#define SCREEN_W		WINDOW_SIZE.x				// 画面の横幅
#define SCREEN_H		WINDOW_SIZE.y				// 画面の縦幅
#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
#define DOWN_SCALE_SCREEN_W	( SCREEN_W / DOWN_SCALE )	// ガウスフィルタを掛ける画像の横幅
#define DOWN_SCALE_SCREEN_H	( SCREEN_H / DOWN_SCALE )	// ガウスフィルタを掛ける画像の縦幅
int ColorScreen;	// 普通の描画結果を書き込むスクリーン
int HighBrightScreen;	// 普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
int DownScaleScreen;	// 高輝度部分を縮小した結果を書き込むスクリーン
int GaussScreen;	// 縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン
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
	// 通常の描画結果を書き込むスクリーンと、フィルターの処理結果を書き込むスクリーンの作成
	ColorScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	HighBrightScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	DownScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	GaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	int Angle;		// カメラの水平角度
	int StageModel;	// ステージモデル
	int GaussRatio;	// ガウスフィルタのぼかし度合い
	// カメラの角度とガウスフィルタのぼかし度合いを初期化
	Angle = 0;
	GaussRatio = 900;

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
		collisionManager_->CheckAllCollisions(player->GetPos(),30.0f);

#pragma region ブルーム前処理
		// 通常の描画結果を書き込むスクリーンを描画対象にする
		SetDrawScreen(ColorScreen);

		// 画面をクリア
		ClearDrawScreen();

		// カメラの位置と向きを設定
		SetCameraPositionAndAngle(VGet(0.0f, 120.0f, 0.0f), 0.0f, Angle / 180.0f * 3.14159f, 0.0f);
#pragma endregion ブルーム前処理

		// ブルーム描画処理
		player->Draw();
		enemyManager->Draw();


#pragma region ブルーム後処理
		//// 左右キーが押されたらカメラを回転する
		//if (CheckHitKey(KEY_INPUT_LEFT))
		//{
		//	Angle -= 3;
		//	if (Angle < 0)
		//	{
		//		Angle += 360;
		//	}
		//}
		//if (CheckHitKey(KEY_INPUT_RIGHT))
		//{
		//	Angle += 3;
		//	if (Angle > 360)
		//	{
		//		Angle -= 360;
		//	}
		//}

		//// 上下キーが押されたらガウスフィルタのぼかし度合いを変更する
		//if (CheckHitKey(KEY_INPUT_UP))
		//{
		//	GaussRatio++;
		//}
		//if (CheckHitKey(KEY_INPUT_DOWN))
		//{
		//	if (GaussRatio > 0)
		//		GaussRatio--;
		//}

		// 描画結果から高輝度部分のみを抜き出した画像を得る
		GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

		// 高輝度部分を８分の１に縮小した画像を得る
		GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

		// ８分の１に縮小した画像をガウスフィルタでぼかす
		GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);


		// 描画対象を裏画面にする
		SetDrawScreen(DX_SCREEN_BACK);


		// 通常の描画結果を描画する
		DrawGraph(0, 0, ColorScreen, FALSE);


		// 描画モードをバイリニアフィルタリングにする( 拡大したときにドットがぼやけるようにする )
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		// 描画ブレンドモードを加算にする
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		// 高輝度部分を縮小してぼかした画像を画面いっぱいに２回描画する( ２回描画するのはより明るくみえるようにするため )
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);

		// 描画ブレンドモードをブレンド無しに戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		// 描画モードを二アレストに戻す
		SetDrawMode(DX_DRAWMODE_NEAREST);


		// 現在のガウスフィルタのぼかし度合いを描画する
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "Gauss:%d", GaussRatio);
#pragma endregion ブルーム後処理

		//UI描画処理(ブルームなし)
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
