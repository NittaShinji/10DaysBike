#include "DxLib.h" 
#include "Inform.h" 
#include "KeyboardInput.h" 
#include "Player.h" 
#include "PlayerState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EnergyGauge.h"
#include "BackGround.h"
#include "SceneManager.h"
#include "AbstractSceneFactory.h"
#include "SceneFactory.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResultScene.h"

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
	//�V�[���t�@�N�g���[
	std::unique_ptr<AbstractSceneFactory> sceneFactory_ = nullptr;
	//�V�[���t�@�N�g���[�𐶐����A�}�l�[�W���ɃZ�b�g
	sceneFactory_ = std::make_unique<SceneFactory>();
	SceneManager::GetInstance()->SetSceneFactory(std::move(sceneFactory_));
	//�V�[���}�l�[�W���ɍŏ��̃V�[�����Z�b�g
	SceneManager::GetInstance()->Initialize();
	SceneManager::GetInstance()->ChangeScene("GAME");
	TitleScene::StaticInitialize();
	GameScene::StaticInitialize();
	ResultScene::StaticInitialize();

	// �Q�[�����[�v
	while (true) {

		KeyboardInput::GetInstance().Update();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		SceneManager::GetInstance()->Update();

		//-------------�`��-------------
		
		//�Q�[���V�[���̕`��
		SceneManager::GetInstance()->Draw();

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
