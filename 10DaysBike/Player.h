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
	static const uint16_t PROT_PLAYER_DRAWING_SIZE = 40;
	static const ColorDxLib PROT_PLAYER_COLOR;
	static const int TURN_KEY = KEY_INPUT_Z;
	static const int BURST_KEY = KEY_INPUT_X;
public:
	//�摜�̎��
	enum struct ImageIndex
	{
		RUN,
		CURVE,
	};
	//�X���̎���
	enum struct CurveImageIndex
	{
		NORMAL,
		INCLI1,
		INCLI2,
	};

	static const uint16_t IMAGE_SIZE = 256;
	static const float IMAGE_EXTEND;

	static const std::string NORMAL_IMAGE_NAME;
	static const std::string CURVE_IMAGE_NAME;
	static const float DOWN_IMAGE_ANGLE;

	static const int CURVE_ANIME_INTERVAL = 5;
	static const int NORMAL_ANIME_INTERVAL = 8;

private:
	static const uint8_t NORMAL_IMAGE_NUM = 3;
	static const uint8_t CURVE_IMAGE_NUM = 3;
private:
	//�O�Ղ̊Ǘ��N���X
	std::unique_ptr<TrajectoriesManager> trajManag_ = nullptr;
	//�X�e�[�g
	std::unique_ptr<IPlayerState>state_ = nullptr;
	//�v���C���[�̃R���C�_�[
	std::unique_ptr<CircleCollider> playerCollider_ = nullptr;
	//�����������ǂ���
	bool isHit_ = false;
	//�ړ��X�s�[�h�̔{��(�o�[�X�g�p��)
	float moveSpeedRate_ = 1.0f;

	int normalImageHandles_[NORMAL_IMAGE_NUM];
	int curveImageHandles_[CURVE_IMAGE_NUM];
	uint8_t imageIndex_ = 0;

public:
	~Player();
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Update(std::function<bool(float)>shootGaugeFunc,
		std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc,
		float rimitY);
	void Draw()override;
	void DrawImage(const std::string& imageName, float angle, bool imageSideTurn);
public:
	void ChangeState(std::unique_ptr<IPlayerState> state);
	void ProccesingNewTrajs();
	void TrajManagerPosUpdate();
public:
	void SetMoveSpeedRate(float rate) { moveSpeedRate_ = rate; }
	float GetMoveSpeedRate() { return moveSpeedRate_; }
public:
	void  IncrementImageIndex(const std::string& imageName);
	void  ImageIndexReset() { imageIndex_ = 0; }

public:
	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;
};

