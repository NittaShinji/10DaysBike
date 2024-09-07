#include "DxLib.h" 
#include "Inform.h" 
#include "KeyboardInput.h" 
#include "Player.h" 
#include "PlayerState.h" 
#include "Enemy.h" 
#include "EnemyState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"

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
	auto player = std::make_unique<Player>();
	player->Init({ WINDOW_SIZE.x / 2,WINDOW_SIZE.y / 2 });

	/*std::unique_ptr <Enemy> enemy = std::make_unique<Enemy>();
	enemy->Init({ 420,236 });*/

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
		player->Update();
		enemyManager->Update();
		//enemy->Update();

		//�S�Ă̏Փ˂��`�F�b�N
		collisionManager_->CheckAllCollisions();

		// �`�揈��
		player->Draw();
		enemyManager->Draw();
		//enemy->Draw();

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
