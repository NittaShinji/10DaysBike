#pragma once
#include "BaseScene.h"
#include "Player.h" 
#include "PlayerState.h" 
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "EnergyGauge.h"
#include "BackGround.h"
#include "Score.h"
#include "Easing.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene : public BaseScene
{
public:

	//�ÓI������
	static void StaticInitialize();

	//���\�[�X�폜
	static void DeleteResource();

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
	std::unique_ptr <Score> score_ = nullptr;

	//�Փ˃}�l�[�W���[
	static CollisionManager* collisionManager_;
	//�w�i�N���X
	std::unique_ptr <BackGround> backGround = nullptr;

	//�Q�[����BGM
	static int bgmHandle_;
	//�X�^�[�g��
	static int startHandle_;
	//UI�摜
	static int uiHandle_;
	//Finish�摜
	static int finishHandle_;
	//�����摜
	static int explainHandle_;

	const Vec2 kDefaultPos_ = { 14 + UI_SIZE.x,-150};
	const Vec2 kDropPos_ = { 0,300 };

	Vec2 finishPos_;

	bool isStartFinishAnime_ = false;

	const float kEasingTime_ = 60.0f;
	EasingInfo resultOutEasing_ = { 0.0f, 300.0f, 0.0f, kEasingTime_ };

	const float kWaitTime_ = 90.0f;
	float waitTime_ = kWaitTime_;

	const float kExplainTime_ = 165.0f;
	float explainTime_ = kWaitTime_;

	bool isStart_ = false;
};

