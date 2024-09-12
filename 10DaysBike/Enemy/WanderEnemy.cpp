#include "WanderEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"
#include"MathFunc.h"

WanderEnemy::~WanderEnemy()
{
	DeleteGraph(graphHandle_);
}

void WanderEnemy::Init(const Vec2& pos, Vec2* targetPos)
{
	//������
	IEnemy::Init(pos, "WanderEnemy");

	//�摜�ǂݍ���
	graphHandle_ = LoadGraph((RESOUCE_PATH + "batEnemy.png").c_str());

	IEnemy::AddCollider();

	targetPos_ = *(targetPos);
	targetPosPtr_ = targetPos;


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
	const int* handles = nullptr;
	DrawGraph(pos_.x - radius_, pos_.y - radius_, graphHandle_, FALSE);
}

//----------------------------------------------------------------------

void WanderEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}
