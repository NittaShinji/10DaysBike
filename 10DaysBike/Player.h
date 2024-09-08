#pragma once
#include"IObject2D.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include<functional>

//�O���錾
class IPlayerState;

//�v���C���[
class Player : public IObject2D
{
public:
	static const float AUTO_MOVING_SPEED;
	static const float SIDE_MOVING_SPEED;
	static const uint16_t PROT_PLAYER_DRAWING_SIZE = 30;
	static const ColorDxLib PROT_PLAYER_COLOR;
	static const int TURN_KEY = KEY_INPUT_SPACE;
private:
	//�O�Ղ̊Ǘ��N���X
	std::unique_ptr<TrajectoriesManager> trajManag_ = nullptr;
	//�X�e�[�g
	std::unique_ptr<IPlayerState>state_ = nullptr;
	//�v���C���[�̃R���C�_�[
	std::unique_ptr<CircleCollider> playerCollider_ = nullptr;
	//�����������ǂ���
	bool isHit_ = false;

private:
	void MoveUpdate();
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Update(std::function<bool(float)>shootGaugeFunc,
		std::function<bool(float, float)> chargeGaugeFunc,
		float rimitY);
	void Draw()override;
public:
	void ChangeState(std::unique_ptr<IPlayerState> state);
	void ProccesingTurning();
	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;
};

