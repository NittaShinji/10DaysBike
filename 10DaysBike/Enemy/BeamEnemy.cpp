#include "BeamEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

const double BeamEnemy::kBeamEnemyImageScale_ = 1.0f;

BeamEnemy::~BeamEnemy()
{
	// 読み込んだ画像のグラフィックハンドルを削除
	for (int i = 0; i < kBeamEnemyImageNum_; i++)
	{
		DeleteGraph(graphHandle_[i]);
	}
}

void BeamEnemy::Init(const Vec2& pos, float bulletSpeed)
{
	//画像読み込み
	LoadDivGraph((RESOUCE_PATH + "BeamEnemy.png").c_str(), 3, 3, 1, 64, 64, graphHandle_);

	//初期化
	IBulletEnemy::Init(pos, bulletSpeed, "BeamEnemy");
	imageNum_ = 0;
	hp_ = 1000;
	actionPhase_ = Charge;
	isTopBullet_ = true;

	//ステート
	ChangeState(std::make_unique<EnemyStateNonAction>());

	if (pattern_ == 0) {
		isInvMove_ = false;
				   
	}			   
	else {		   
		isInvMove_ = true;
	}
}

void BeamEnemy::Update()
{
	IBulletEnemy::Update();
	if (actionPhase_ == Charge) {
		chargeCount_++;
		if (chargeCount_ >= kMaxChargeCount_) {
			chargeCount_ = 0;
			isTopBullet_ = true;
			actionPhase_ = Shot;
		}

		//移動処理
		if (isInvMove_ == false) {
			moveVec_ = kMoveSpeed_;
		}
		else {
			moveVec_ = kMoveSpeed_;
			moveVec_.x *= -1;
		}

		

		pos_ += moveVec_;
	}
	else if (actionPhase_ == Shot) {

		shotCount_++;
		bulletShotCount_++;
		if (shotCount_ < kMaxShotCount_) {

			if (bulletShotCount_ >= kBulletShotCount_) {
				//弾を生成し、初期化
				std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
				newBullet->Initialize(pos_, { 0,-12.f });
				if (isTopBullet_ == true) {
					isTopBullet_ = false;

					newBullet->SetGraph(bulletManager_->beamLineGraph_);
				}
				else {
					newBullet->SetGraph(bulletManager_->beamTopGraph_);
				}

				//弾を弾マネージャーに登録する
				bulletManager_->GetBullets().push_back(std::move(newBullet));
				bulletShotCount_ = 0;

			}


		}
		else {
			shotCount_ = 0;
			actionPhase_ = Delay;

		}
	}
	else if (actionPhase_ == Delay) {
		delayCount_++;
		if (delayCount_ >= kMaxDelayCount_) {
			delayCount_ = 0;
			actionPhase_ = Charge;
		}
	}

	


}

void BeamEnemy::Draw()
{
	IBulletEnemy::Draw();
	const int* handles = nullptr;
	DrawRotaGraph(pos_.x, pos_.y, kBeamEnemyImageScale_, angle_, graphHandle_[imageNum_], TRUE, FALSE);
}

void BeamEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}
