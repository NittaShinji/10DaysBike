#include "DxLib.h" 
#include "Inform.h" 
#include "KeyboardInput.h" 
#include "Player.h" 
#include "PlayerState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EnergyGauge.h"

// �X�N���[���ϐ�
#define SCREEN_W		WINDOW_SIZE.x				// ��ʂ̉���
#define SCREEN_H		WINDOW_SIZE.y				// ��ʂ̏c��
#define DOWN_SCALE		8				// �K�E�X�t�B���^���|����摜����ʂ̃T�C�Y�̉����̂P��
#define DOWN_SCALE_SCREEN_W	( SCREEN_W / DOWN_SCALE )	// �K�E�X�t�B���^���|����摜�̉���
#define DOWN_SCALE_SCREEN_H	( SCREEN_H / DOWN_SCALE )	// �K�E�X�t�B���^���|����摜�̏c��
int ColorScreen;	// ���ʂ̕`�挋�ʂ��������ރX�N���[��
int HighBrightScreen;	// ���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
int DownScaleScreen;	// ���P�x�������k���������ʂ��������ރX�N���[��
int GaussScreen;	// �k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��
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
	// �ʏ�̕`�挋�ʂ��������ރX�N���[���ƁA�t�B���^�[�̏������ʂ��������ރX�N���[���̍쐬
	ColorScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	HighBrightScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	DownScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	GaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	int Angle;		// �J�����̐����p�x
	int StageModel;	// �X�e�[�W���f��
	int GaussRatio;	// �K�E�X�t�B���^�̂ڂ����x����
	// �J�����̊p�x�ƃK�E�X�t�B���^�̂ڂ����x������������
	Angle = 0;
	GaussRatio = 900;

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	auto player = std::make_unique<Player>();
	player->Init({ WINDOW_SIZE.x / 2,WINDOW_SIZE.y / 2 });

	auto gauge = std::make_unique<EnergyGauge>();
	gauge->Init();

	std::unique_ptr <EnemyManager> enemyManager = std::make_unique<EnemyManager>();
	enemyManager->Init();

	//�Փ˃}�l�[�W���[
	CollisionManager* collisionManager_ = nullptr;
	collisionManager_ = CollisionManager::GetInstance();

	// �Q�[�����[�v
	while (true) {

		KeyboardInput::GetInstance().Update();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		player->Update([&](float shootGaugeDecre) { return gauge->DecreGaugeRatio(shootGaugeDecre); },
			[&](float posY, float shootChargeGauge) { return gauge->ChargeGaugeRatio(posY, shootChargeGauge); },
			gauge->FRAME_TOP);
		enemyManager->Update();
		gauge->Update();

		//�S�Ă̏Փ˂��`�F�b�N
		collisionManager_->CheckAllCollisions(player->GetPos(),30.0f);

#pragma region �u���[���O����
		// �ʏ�̕`�挋�ʂ��������ރX�N���[����`��Ώۂɂ���
		SetDrawScreen(ColorScreen);

		// ��ʂ��N���A
		ClearDrawScreen();

		// �J�����̈ʒu�ƌ�����ݒ�
		SetCameraPositionAndAngle(VGet(0.0f, 120.0f, 0.0f), 0.0f, Angle / 180.0f * 3.14159f, 0.0f);
#pragma endregion �u���[���O����

		// �u���[���`�揈��
		player->Draw();
		enemyManager->Draw();


#pragma region �u���[���㏈��
		//// ���E�L�[�������ꂽ��J��������]����
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

		//// �㉺�L�[�������ꂽ��K�E�X�t�B���^�̂ڂ����x������ύX����
		//if (CheckHitKey(KEY_INPUT_UP))
		//{
		//	GaussRatio++;
		//}
		//if (CheckHitKey(KEY_INPUT_DOWN))
		//{
		//	if (GaussRatio > 0)
		//		GaussRatio--;
		//}

		// �`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
		GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

		// ���P�x�������W���̂P�ɏk�������摜�𓾂�
		GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

		// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
		GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);


		// �`��Ώۂ𗠉�ʂɂ���
		SetDrawScreen(DX_SCREEN_BACK);


		// �ʏ�̕`�挋�ʂ�`�悷��
		DrawGraph(0, 0, ColorScreen, FALSE);


		// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���( �g�債���Ƃ��Ƀh�b�g���ڂ₯��悤�ɂ��� )
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		// �`��u�����h���[�h�����Z�ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		// ���P�x�������k�����Ăڂ������摜����ʂ����ς��ɂQ��`�悷��( �Q��`�悷��̂͂�薾�邭�݂���悤�ɂ��邽�� )
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);

		// �`��u�����h���[�h���u�����h�����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		// �`�惂�[�h���A���X�g�ɖ߂�
		SetDrawMode(DX_DRAWMODE_NEAREST);


		// ���݂̃K�E�X�t�B���^�̂ڂ����x������`�悷��
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "Gauss:%d", GaussRatio);
#pragma endregion �u���[���㏈��

		//UI�`�揈��(�u���[���Ȃ�)
		gauge->Draw();

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
