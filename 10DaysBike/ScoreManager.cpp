#include "ScoreManager.h"
#include "Vec2.h"
#include "KeyboardInput.h"
#include "Inform.h"
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

void ScoreManager::Load()
{
	
}

void ScoreManager::Init()
{
	totalScore_ = std::make_unique<Score>();
	totalScore_->Init(Vec2(500,500));

    resultScore_ = std::make_unique<Score>();
    resultScore_->Init(Vec2(500,700));
	Score::Load();

	goldScore_ = std::make_unique<Score>();
	silberScore_ = std::make_unique<Score>();
	bronzeScore_ = std::make_unique<Score>();
	goldScore_->SetPos(Vec2(484, 480));
	silberScore_->SetPos(Vec2(484, 580));
	bronzeScore_->SetPos(Vec2(484, 680));
}

void ScoreManager::Update()
{
	totalScore_->Update();
}

void ScoreManager::Draw()
{
	totalScore_->Draw();
	//ランキングの表示
}

void ScoreManager::Reset()
{
    totalScore_->Reset();
}

void ScoreManager::ResetInit()
{
    int gameScore =  totalScore_->GetTargetScore();
    resultScore_->SetTargetScore(gameScore);
}

void ScoreManager::ResetUpdate()
{
    resultScore_->Update();
	goldScore_->Update();
	silberScore_->Update();
	bronzeScore_->Update();
	int registScore = totalScore_->GetTargetScore();
	if (registScore > ranking[2] && isRegistRanking_ == false)
	{
		isJugeRegeist = true;
	}
}

void ScoreManager::ResetDraw()
{
    resultScore_->Draw();
}

void ScoreManager::RegistScore(std::vector<std::string>& deadEnemyNames)
{
    bool scoreAdded = false;

	for (std::string& deadEnemyName : deadEnemyNames)
	{
        for (std::string& deadEnemyName : deadEnemyNames)
        {
            if (deadEnemyName == "BadEnemy")
            {
                totalScore_->AddScore(100);
                scoreAdded = true;
            }
            else if (deadEnemyName == "BeamEnemy")
            {
                totalScore_->AddScore(500);
                scoreAdded = true;
            }
            else if (deadEnemyName == "BulletFlyEnemy")
            {
                totalScore_->AddScore(1000);
                scoreAdded = true;
            }
            else if (deadEnemyName == "WanderEnemy")
            {
                totalScore_->AddScore(200);
                scoreAdded = true;
            }
        }

        if (scoreAdded)
        {
            totalScore_->SetIsDrum(true);
        }
	}

    if (scoreAdded)
    {
        // 新しいスコアに合わせて目標スコアを設定
        totalScore_->SetTargetScore(totalScore_->GetScore());

        // ドラムロールを開始
        totalScore_->SetIsDrum(true);
        totalScore_->SetDrumTimer(0.0f);  // ドラムロールのタイマーをリセット
    }

	// deadEnemyNamesを空にする
	deadEnemyNames.clear();
}

void ScoreManager::InitRanking()
{
	// 入力処理
	if (!isLoggedIn) {
		
			if (!isConnectingToAPI) {
				isConnectingToAPI = true;
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

				goldScore_->SetScore(ranking[0]);
				silberScore_->SetScore(ranking[1]);
				bronzeScore_->SetScore(ranking[2]);
			}
		}
		catch (const std::exception& e) {
			DrawFormatString(250, 240 - 32, stringCr, "ERROR exception::%s\n", e.what());
		}
	}
}

void ScoreManager::UpdateRanking()
{
	goldScore_->Update();
	silberScore_->Update();
	bronzeScore_->Update();
}

void ScoreManager::RegistRanking()
{
	int registScore = totalScore_->GetTargetScore();

	if (registScore > ranking[2] && isRegistRanking_ == false)
	{
		//APIに通信する
		if (true)
		{
			try {
				//post通信を行う

				auto serverStatusCode = Post(L"https://swgame-dusky.vercel.app/scores/", registScore, token).wait();

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
					}
					goldScore_->SetScore(ranking[0]);
					silberScore_->SetScore(ranking[1]);
					bronzeScore_->SetScore(ranking[2]);
					isRegistRanking_ = true;
					isJugeRegeist = false;
				}
			}
			catch (const std::exception& e) {
				//例外処理
				DrawFormatString(250, 240 - 32, stringCr, "ERROR exception::%s\n", e.what());
			}
		}
	}
}

void ScoreManager::DrawRanking()
{
	goldScore_->Draw();
	silberScore_->Draw();
	bronzeScore_->Draw();
}

void ScoreManager::SetNotRankDrumRoll()
{
	goldScore_->SetIsDrum(false);
	silberScore_->SetIsDrum(false);
	bronzeScore_->SetIsDrum(false);
}
