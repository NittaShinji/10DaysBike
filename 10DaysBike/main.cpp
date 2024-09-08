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

using namespace utility;				// ������ϊ��Ȃǂ̈�ʓI�ȃ��[�e�B���e�B
using namespace web;					// URI�̂悤�ȋ��ʂ̋@�\
using namespace web::http;				// ���ʂ�HTTP�@�\
using namespace web::http::client;		// HTTP �N���C�A���g�̋@�\
using namespace concurrency::streams;	// �񓯊��X�g���[��

template<class T>
pplx::task<T> Get(const std::wstring& url, const std::wstring& token) {
	return pplx::create_task([=] {
		// �N���C�A���g�̐ݒ�
		http_client client(url);
		http_request req(methods::GET);
		req.set_request_uri(::utility::conversions::to_string_t(L""));
		req.headers().add(L"Authorization", L"Bearer " + token);
		return client.request(req, pplx::cancellation_token::none());
	})
		.then([](http_response response) {
		// �X�e�[�^�X�R�[�h����
		if (response.status_code() == status_codes::OK) {
			// ���X�|���X�{�f�B��\��
			return response.extract_json();
		}
		else {
			throw std::runtime_error("Received non-OK HTTP status code");
		}
	});
}

pplx::task<int> Post(const std::wstring& url, int score, const std::wstring& token) {
	return pplx::create_task([=] {
		// ���M�f�[�^�̍쐬
		json::value postData;
		postData[L"score"] = score;

		// �N���C�A���g�̐ݒ�
		http_client client(url);
		http_request req(methods::POST);
		req.set_request_uri(::utility::conversions::to_string_t(L""));
		req.set_body(postData.serialize(), L"application/json");
		req.headers().add(L"Authorization", L"Bearer " + token);

		// ���N�G�X�g���M
		//return client.request(methods::POST, L"", postData.serialize(), L"application/json");
		return client.request(req, pplx::cancellation_token::none());
	})
		.then([](http_response response) {
		// �X�e�[�^�X�R�[�h����
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
		// ���M�f�[�^�̍쐬
		json::value postData;
		postData[L"name"] = json::value::string(L"Game1");
		postData[L"password"] = json::value::string(L"kamata04");

		// �N���C�A���g�̐ݒ�
		http_client client(url);

		// ���N�G�X�g���M
		return client.request(methods::POST, L"", postData.serialize(), L"application/json");
	})
		.then([](http_response response) {
		// �X�e�[�^�X�R�[�h����
		if (response.status_code() == status_codes::OK) {
			return response.extract_json();
		}
		else {
			throw std::runtime_error("Received non-OK HTTP status code");
		}
	});
}

// �E�B���h�E�̃^�C�g���ɕ\�����镶����

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE.c_str());

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	//�Q�[���̗���
	enum Gameflow {
		BeforeGame,
		InGame,
		RegistScore,
		Result,
	};

	Gameflow gameFlow_ = BeforeGame;

	//�X�R�A�֘A
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

	//�Փ˃}�l�[�W���[
	CollisionManager* collisionManager_ = nullptr;
	collisionManager_ = CollisionManager::GetInstance();

	const unsigned int stringCr = GetColor(255, 255, 255);

	int scoreNum = 100;

	// �Q�[�����[�v
	while (true) {

		KeyboardInput::GetInstance().Update();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//player->Update();
		//enemyManager->Update();
		//score->Update(enemyManager->GetEnemyDeadNum());
		//�S�Ă̏Փ˂��`�F�b�N
		//collisionManager_->CheckAllCollisions();

		//---------------------------------------------------------------------------------

		switch (gameFlow_)
		{

			//�Q�[���J�n�O
		case BeforeGame:

			// ���͏���
			if (!isLoggedIn) {
				if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_Q)) {
					if (!isConnectingToAPI) {
						isConnectingToAPI = true;
					}
				}
			}

			// API�ɒʐM����
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

						// ����������GET�ʐM�Ń����L���O���擾����
						auto task = Get<json::value>(L"https://swgame-dusky.vercel.app/scores/", token);
						const json::value j = task.get();
						auto array = j.as_array();

						// json�I�u�W�F�N�g����K�v�ȕ��������o����int�^�̔z��ɑ��
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

		//�Q�[����
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

		//�X�R�A�o�^��
		case RegistScore:

			//API�ɒʐM����
			if (true)
			{
				try {
					//post�ʐM���s��

					auto serverStatusCode = Post(L"https://swgame-dusky.vercel.app/scores/", scoreNum, token).wait();

					//�X�R�A�̓o�^������������A�����L���O���擾����BPOST�����܂�������1���Ԃ��Ă���
					if (serverStatusCode == 1)
					{
						//���e�ɐ���������GET�ʐM�Ń����L���O���擾����
						auto task = Get<json::value>(L"https://swgame-dusky.vercel.app/scores/", token);
						const json::value j = task.get();
						auto array = j.as_array();

						//json�I�u�W�F�N�g����K�v�ȕ��������o����int�^�̔z��ɑ��
						for (int i = 0; i < array.size(); i++)
						{
							ranking[i] = array[i].at(U("score")).as_integer();
							gameFlow_ = Result;
						}
					}
				}
				catch (const std::exception& e) {
					//��O����
					DrawFormatString(250, 240 - 32, stringCr, "ERROR exception::%s\n", e.what());
				}
			}
			break;

		case Result:

			//�^�C�g����ʂɖ߂�
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

		// �`�揈��
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

		//�����L���O��\��
		for (int i = 0; i < kRankNum; i++) {
			DrawFormatString(100, i * 20 + 100, stringCr,"%drank : %d", i + 1, ranking[i]);
		}



		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
