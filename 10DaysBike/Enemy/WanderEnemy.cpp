#include "WanderEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"
#include"MathFunc.h"

WanderEnemy::~WanderEnemy()
{
	// 読み込んだ画像のグラフィックハンドルを削除
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(graphHandle_[i]);
	}
}

void WanderEnemy::Init(const Vec2& pos, Vec2* targetPos)
{
	//初期化
	IEnemy::Init(pos, "WanderEnemy");

	//画像読み込み
	LoadDivGraph((RESOUCE_PATH + "BombEnemy.png").c_str(), 8, 8,
		1,  64, 64, graphHandle_);

	IEnemy::AddCollider();

	targetPos_ = *(targetPos);
	targetPosPtr_ = targetPos;

	hp_ = 24;
}

void WanderEnemy::Update()
{
	//枚フレーム保存処理
	oldMoveVec_ = moveVec_;
	homingFlameCount_;//何フレームに1回処理するか


	//ホーミングの処理
	isHomingCount_++;
	if (isHomingCount_ > kMaxHomingCount_ && isHoming_ == true) {
		isHoming_ = false;
	}

	Vec2 targetLenVec = pos_ - *(targetPosPtr_);
	float targetLen = targetLenVec.GetLength();
	targetLen = fabsf(targetLen);
	if (targetLen < kNearLen_) {	//近づいたらホーミングを解く
		isHoming_ = false;
	}

	//挙動処理
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
		drawPos_.x += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // ランダムに震える
		drawPos_.y += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // ランダムに震える
		
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
