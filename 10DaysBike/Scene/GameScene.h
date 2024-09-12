#pragma once
#include "BaseScene.h"
#include "Player.h" 
#include "PlayerState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EnergyGauge.h"
#include "BackGround.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene : public BaseScene
{
public:

	//�ÓI������
	static void StaticInitialize();

	//������
	void Initialize() override;

	//���t���[���X�V
	void Update() override;

	//�`��
	void Draw() override;

private:

	//�u���[��
	int ColorScreen;	// ���ʂ̕`�挋�ʂ��������ރX�N���[��
	int HighBrightScreen;	// ���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
	int DownScaleScreen;	// ���P�x�������k���������ʂ��������ރX�N���[��
	int GaussScreen;	// �k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��
	int Angle;		// �J�����̐����p�x
	int StageModel;	// �X�e�[�W���f��
	int GaussRatio;	// �K�E�X�t�B���^�̂ڂ����x����

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	std::unique_ptr <Player> player = nullptr;
	std::unique_ptr <EnergyGauge> gauge = nullptr;
	std::unique_ptr <EnemyManager> enemyManager = nullptr;
	
	//�Փ˃}�l�[�W���[
	static CollisionManager* collisionManager_;
	//�w�i�N���X
	std::unique_ptr <BackGround> backGround = nullptr;
};

