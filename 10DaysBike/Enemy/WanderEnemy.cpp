#include "WanderEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"
#include"MathFunc.h"

WanderEnemy::~WanderEnemy()
{
	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(graphHandle_[i]);
	}
}

void WanderEnemy::Init(const Vec2& pos, Vec2* targetPos)
{
	//������
	IEnemy::Init(pos, "WanderEnemy");

	//�摜�ǂݍ���
	LoadDivGraph((RESOUCE_PATH + "BombEnemy.png").c_str(), 8, 8,
		1,  64, 64, graphHandle_);

	IEnemy::AddCollider();

	targetPos_ = *(targetPos);
	targetPosPtr_ = targetPos;

	hp_ = 24;
}

void WanderEnemy::Update()
{
	//���t���[���ۑ�����
	oldMoveVec_ = moveVec_;
	homingFlameCount_;//���t���[����1�񏈗����邩


	//�z�[�~���O�̏���
	isHomingCount_++;
	if (isHomingCount_ > kMaxHomingCount_ && isHoming_ == true) {
		isHoming_ = false;
	}

	Vec2 targetLenVec = pos_ - *(targetPosPtr_);
	float targetLen = targetLenVec.GetLength();
	targetLen = fabsf(targetLen);
	if (targetLen < kNearLen_) {	//�߂Â�����z�[�~���O������
		isHoming_ = false;
	}

	//��������
	moveVelocity_ += kAddVelocity_;

	float dx = targetPos_.x - pos_.x;
	float dy = targetPos_.y - pos_.y;
	float distance = sqrt(dx * dx + dy * dy);

	if (isHoming_ == true && (homingFlameCount_ % excuteHomingFlameCount_ == 0)) {
		moveVec_ = *(targetPosPtr_)-pos_;

		float delta;
		float sampleAngle = moveVec_.AngleDeg() - oldMoveVec_.AngleDeg();
		if (sampleAngle == 0) {
			delta = 0;
		}
		else {
			delta = MathFunc::DeltaAngle(moveVec_.AngleDeg() - oldMoveVec_.AngleDeg(), 360.f);
		}

		float angle;
		if (delta > 0) {
			angle = moveVec_.AngleDeg() + homingAngle_;
			moveVec_ = MathFunc::AngleToVector(angle);
		}
		else if (delta < 0) {
			angle = moveVec_.AngleDeg() - homingAngle_;
			moveVec_ = MathFunc::AngleToVector(angle);
		}
		 
		moveVec_ = moveVec_.GetNormalize();
		moveVec_ *= moveVelocity_;


	}
	else {
		moveVec_ = oldMoveVec_;
		moveVec_ = moveVec_.GetNormalize();
		moveVec_ *= moveVelocity_;
	}

	pos_ += moveVec_;


	IEnemy::Update();
}

void WanderEnemy::Draw()
{
	IEnemy::Draw();
	
	const int shakeRange = 2;
	if (isHit_ == true)
	{
		drawPos_.x += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // �����_���ɐk����
		drawPos_.y += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // �����_���ɐk����
		
		DrawRotaGraph(drawPos_.x, drawPos_.y, 0.7f, angle_, graphHandle_[1], TRUE, FALSE);
	}
	else {
		DrawRotaGraph(drawPos_.x, drawPos_.y, 0.7f, angle_, graphHandle_[1], TRUE, FALSE);
	}
	
}

//----------------------------------------------------------------------

void WanderEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}
