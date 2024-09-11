#include "WanderEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

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
	//�O�t���[���ۑ�����
	oldMoveVec_ = moveVec_;

	//�z�[�~���O�̏���
	homingCount_++;
	if (homingCount_ > kMaxHomingCount_ && isHoming_ == true) {
		isHoming_ = false;
	}

	//��������
	moveVelocity_ += kAddVelocity_;

	float dx = targetPos_.x - pos_.x;
	float dy = targetPos_.y - pos_.y;
	float distance = sqrt(dx * dx + dy * dy);

	if (isHoming_ == true) {
		moveVec_ = *(targetPosPtr_)-pos_;
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
