#include "GameScene.h"
#include "KeyboardInput.h"
#include "SceneManager.h"

// �X�N���[���ϐ�
#define SCREEN_W		WINDOW_SIZE.x				// ��ʂ̉���
#define SCREEN_H		WINDOW_SIZE.y				// ��ʂ̏c��
#define DOWN_SCALE		8				// �K�E�X�t�B���^���|����摜����ʂ̃T�C�Y�̉����̂P��
#define DOWN_SCALE_SCREEN_W	( SCREEN_W / DOWN_SCALE )	// �K�E�X�t�B���^���|����摜�̉���
#define DOWN_SCALE_SCREEN_H	( SCREEN_H / DOWN_SCALE )	// �K�E�X�t�B���^���|����摜�̏c��

CollisionManager* GameScene::collisionManager_ = nullptr;

void GameScene::StaticInitialize()
{
	collisionManager_ = CollisionManager::GetInstance();
	Score::Load();
}

void GameScene::Initialize()
{
	//�o�^���Ă����R���C�_�[��S�č폜(�I�u�W�F�N�g�̏������O�ɍs��(���������ɃR���C�_�[��ǉ����邽��))
	collisionManager_->RemoveCollider();

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	// �ʏ�̕`�挋�ʂ��������ރX�N���[���ƁA�t�B���^�[�̏������ʂ��������ރX�N���[���̍쐬
	ColorScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	HighBrightScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	DownScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	GaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	// �J�����̊p�x�ƃK�E�X�t�B���^�̂ڂ����x������������
	Angle = 0;
	GaussRatio = 900;

	//������
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
	// �X�V����
	player->Update([&](float shootGaugeDecre) { return gauge->DecreGaugeRatio(shootGaugeDecre); },
		[&](float posY, float shootChargeGauge) { return gauge->ChargeGaugeRatio(posY, shootChargeGauge); },
		gauge->FRAME_TOP);
	enemyManager->Update();
	gauge->Update();
	backGround->Update(player->GetVec().y, player->GetPlayerState());
	score_->Update();

	//�S�Ă̏Փ˂��`�F�b�N
	collisionManager_->CheckAllCollisions(player->GetPos(), 30.0f);


	if (KeyboardInput::GetInstance().GetTriggerKey(KEY_INPUT_RETURN)) {
		//�N���A�V�[���Ɉړ�
		SceneManager::GetInstance()->ChangeScene("CLEAR");
	}
	else if (! player->GetIsAlive()) {
		//�^�C�g���V�[���Ɉړ�
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}
}

void GameScene::Draw()
{
#pragma region �u���[���O����
	// �ʏ�̕`�挋�ʂ��������ރX�N���[����`��Ώۂɂ���
	SetDrawScreen(ColorScreen);

	// ��ʂ��N���A
	ClearDrawScreen();

	// �J�����̈ʒu�ƌ�����ݒ�
	SetCameraPositionAndAngle(VGet(0.0f, 120.0f, 0.0f), 0.0f, Angle / 180.0f * 3.14159f, 0.0f);
#pragma endregion �u���[���O����

	// �u���[���`�揈��
	backGround->Draw();
	enemyManager->Draw();
	player->Draw();

#pragma region �u���[���㏈��

	// �`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
	GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

	// ���P�x�������W���̂P�ɏk�������摜�𓾂�
	GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

	// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
	GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);

	// �`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �ʏ�̕`�挋�ʂ�`�悷��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255); // �A���t�@�u�����h���[�h�ɐݒ�
	DrawGraph(0, 0, ColorScreen, FALSE);

	// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���( �g�債���Ƃ��Ƀh�b�g���ڂ₯��悤�ɂ��� )
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// �`��u�����h���[�h�����Z�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ���P�x�������k�����Ăڂ������摜����ʂ����ς��ɂQ��`�悷��( �Q��`�悷��̂͂�薾�邭�݂���悤�ɂ��邽�� )
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);

	// �`��u�����h���[�h���A���t�@�u�����h�ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// �`�惂�[�h���A���X�g�ɖ߂�
	SetDrawMode(DX_DRAWMODE_NEAREST);

#pragma endregion �u���[���㏈��

	//UI�`�揈��(�u���[���Ȃ�)
	score_->Draw();
	gauge->Draw();
}
