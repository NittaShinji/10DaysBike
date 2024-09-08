#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
#include "DxLib.h" 
#include "Inform.h" 
#include "KeyboardInput.h" 
#include "Player.h" 
#include "PlayerState.h" 
#include "Enemy.h" 
#include "EnemyState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "Score.h"
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <string>

using namespace utility;				// 文字列変換などの一般的なユーティリティ
using namespace web;					// URIのような共通の機能
using namespace web::http;				// 共通のHTTP機能
using namespace web::http::client;		// HTTP クライアントの機能
using namespace concurrency::streams;	// 非同期ストリーム

template<class T>
pplx::task<T> Get(const std::wstring& url, const std::wstring& token) {
	return pplx::create_task([=] {
		// クライアントの設定
		http_client client(url);
		http_request req(methods::GET);
		req.set_request_uri(::utility::conversions::to_string_t(L""));
		req.headers().add(L"Authorization", L"Bearer " + token);
		return client.request(req, pplx::cancellation_token::none());
	})
		.then([](http_response response) {
		// ステータスコード判定
		if (response.status_code() == status_codes::OK) {
			// レスポンスボディを表示
			return response.extract_json();
		}
		else {
			throw std::runtime_error("Received non-OK HTTP status code");
		}
	});
}

pplx::task<int> Post(const std::wstring& url, int score, const std::wstring& token) {
	return pplx::create_task([=] {
		// 送信データの作成
		json::value postData;
		postData[L"score"] = score;

		// クライアントの設定
		http_client client(url);
		http_request req(methods::POST);
		req.set_request_uri(::utility::conversions::to_string_t(L""));
		req.set_body(postData.serialize(), L"application/json");
		req.headers().add(L"Authorization", L"Bearer " + token);

		// リクエスト送信
		//return client.request(methods::POST, L"", postData.serialize(), L"application/json");
		return client.request(req, pplx::cancellation_token::none());
	})
		.then([](http_response response) {
		// ステータスコード判定
		if (response.status_code() == status_codes::OK) {
			return response.extract_json();
		}
		else {
			throw std::runtime_error("Received non-OK HTTP status code");
		}})
		.then([](json::value json)
	{
		return json[L"status_code"].as_integer();
	});
}

pplx::task<web::json::value> Login(const std::wstring& url) {
	return pplx::create_task([=] {
		// 送信データの作成
		json::value postData;
		postData[L"name"] = json::value::string(L"Game1");
		postData[L"password"] = json::value::string(L"kamata04");

		// クライアントの設定
		http_client client(url);

		// リクエスト送信
		return client.request(methods::POST, L"", postData.serialize(), L"application/json");
	})
		.then([](http_response response) {
		// ステータスコード判定
		if (response.status_code() == status_codes::OK) {
			return response.extract_json();
		}
		else {
			throw std::runtime_error("Received non-OK HTTP status code");
		}
	});
}

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

	//ゲームの流れ
	enum Gameflow {
		BeforeGame,
		InGame,
		RegistScore,
		Result,
	};

	Gameflow gameFlow_ = BeforeGame;

	//スコア関連
	int count = 0;
	const int kRankNum = 5;
	int ranking[500] = { 0 };
	bool isLoggedIn = false;
	bool isConnectingToAPI = false;

	std::string operationStr;
	std::wstring token;

	auto player = std::make_unique<Player>();
	player->Init({ WINDOW_SIZE.x / 2,WINDOW_SIZE.y / 2 });

	std::unique_ptr <EnemyManager> enemyManager = std::make_unique<EnemyManager>();
	enemyManager->Init();

	std::unique_ptr <Score> score = std::make_unique<Score>();
	score->Init();

	//衝突マネージャー
	CollisionManager* collisionManager_ = nullptr;
	collisionManager_ = CollisionManager::GetInstance();

	const unsigned int stringCr = GetColor(255, 255, 255);

	int scoreNum = 100;

	// ゲームループ
	while (true) {

		KeyboardInput::GetInstance().Update();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		//player->Update();
		//enemyManager->Update();
		//score->Update(enemyManager->GetEnemyDeadNum());
		//全ての衝突をチェック
		//collisionManager_->CheckAllCollisions();

		//---------------------------------------------------------------------------------

		switch (gameFlow_)
		{

			//ゲーム開始前
		case BeforeGame:

			// 入力処理
			if (!isLoggedIn) {
				if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_Q)) {
					if (!isConnectingToAPI) {
						isConnectingToAPI = true;
					}
				}
			}

			// APIに通信する
			if (isConnectingToAPI) {
				try {

					auto loginStatus = Login(L"https://swgame-dusky.vercel.app/users/login");
					const json::value loginInfo = loginStatus.get();
					auto loginString = loginInfo.at(L"login_status").as_string();
					token = loginInfo.at(L"token").as_string();

					if (loginString == L"success") {
						isLoggedIn = true;
						isConnectingToAPI = false;
						
						DrawString(250, 240 - 32, "SUCCESS", stringCr);

						// 成功したらGET通信でランキングを取得する
						auto task = Get<json::value>(L"https://swgame-dusky.vercel.app/scores/", token);
						const json::value j = task.get();
						auto array = j.as_array();

						// jsonオブジェクトから必要な部分を取り出してint型の配列に代入
						for (int i = 0; i < array.size(); i++) {
							ranking[i] = array[i].at(U("score")).as_integer();
						}

						gameFlow_ = InGame;
					}
				}
				catch (const std::exception& e) {
					DrawFormatString(250, 240 - 32,stringCr, "ERROR exception::%s\n", e.what());
				}
			}
			break;

		//ゲーム中
		case InGame:

			//if (isStart == false) {
			//	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_E)) {
			//		isStart = true;
			//	}
			//}
			if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
				gameFlow_ = RegistScore;
			}

			break;

		//スコア登録中
		case RegistScore:

			//APIに通信する
			if (true)
			{
				try {
					//post通信を行う

					auto serverStatusCode = Post(L"https://swgame-dusky.vercel.app/scores/", scoreNum, token).wait();

					//スコアの登録が完了したら、ランキングを取得する。POSTがうまくいくと1が返ってくる
					if (serverStatusCode == 1)
					{
						//投稿に成功したらGET通信でランキングを取得する
						auto task = Get<json::value>(L"https://swgame-dusky.vercel.app/scores/", token);
						const json::value j = task.get();
						auto array = j.as_array();

						//jsonオブジェクトから必要な部分を取り出してint型の配列に代入
						for (int i = 0; i < array.size(); i++)
						{
							ranking[i] = array[i].at(U("score")).as_integer();
							gameFlow_ = Result;
						}
					}
				}
				catch (const std::exception& e) {
					//例外処理
					DrawFormatString(250, 240 - 32, stringCr, "ERROR exception::%s\n", e.what());
				}
			}
			break;

		case Result:

			//タイトル画面に戻る
			if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_SPACE)) {
				gameFlow_ = BeforeGame;
			}

			count = 0;
			score = 0;
			isLoggedIn = false;

			break;

			default:
			break;
		}


		//---------------------------------------------------------------------------------

		// 描画処理
		//player->Draw();
		//enemyManager->Draw();
		//score->Draw();

		switch (gameFlow_)
		{
		case BeforeGame:

			DrawString(1000, 100, "TITLE", stringCr);

			break;

		case InGame:

			DrawString(1000, 100, "GAME", stringCr);
			DrawFormatString(100, 360, stringCr,"Score : %d", scoreNum);

			break;

		case RegistScore:

			DrawString(100, 360, "Registing Score", stringCr);
			DrawString(1000, 100, "RegistScore", stringCr);
			break;

		case Result:

			DrawString(100, 360, "Result", stringCr);
			DrawString(100, 380, "Press space to Title", stringCr);
			DrawString(1000, 100, "Result", stringCr);
			break;

		default:
			break;

		}

		//ランキングを表示
		for (int i = 0; i < kRankNum; i++) {
			DrawFormatString(100, i * 20 + 100, stringCr,"%drank : %d", i + 1, ranking[i]);
		}



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
