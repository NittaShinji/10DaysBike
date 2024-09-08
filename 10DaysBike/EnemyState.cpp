#include "Enemy.h"
#include "EnemyState.h"

//----------------------------------------------------
//基底クラス
//void IEnemyState::SideMoveUpdate()
//{
//	const Vec2 SIDE_MOVE_VEC = {
//		KeyboardInput::GetInstance().GetSideVerticalKey().x,
//		0
//	};
//
//	enemy_->SetPos(enemy_->GetPos() + SIDE_MOVE_VEC * Enemy::SIDE_MOVING_SPEED);
//}

void IEnemyState::Update()
{
	/*SideMoveUpdate();

	if (KeyboardInput::GetInstance().GetTriggerKey(Enemy::TURN_KEY))
	{
		isWaitingTurn_ = true;
		enemy_->ProccesingTurning();
	}*/
}


//----------------------------------------------------
//敵の待機状態
void EnemyStateWait::Init()
{
}

void EnemyStateWait::Update()
{
	enemy_->SetPos(enemy_->GetPos());

	IEnemyState::Update();

	if (waitTimer_ >= 0) 
	{
		waitTimer_--;
		if (waitTimer_ < 0)
		{
			enemy_->ChangeState(std::make_unique<EnemyStateAttack>());
		}
	}
	/*if (isWaitingTurn_)
	{
		Enemy_->ChangeState(std::make_unique<EnemyStateDown>());
	}*/
}

void EnemyStateWait::Draw()
{
	const Vec2 pos = enemy_->GetPos();

	const Vec2 BOTTOM = pos - Vec2{ 0, -Enemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 RIGHT_TOP = pos -
		Vec2{ Enemy::PROT_ENEMY_DRAWING_SIZE, Enemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 LEFT_TOP = pos -
		Vec2{ -Enemy::PROT_ENEMY_DRAWING_SIZE, Enemy::PROT_ENEMY_DRAWING_SIZE };

	DrawTriangle(BOTTOM.x, BOTTOM.y, RIGHT_TOP.x, RIGHT_TOP.y, LEFT_TOP.x, LEFT_TOP.y,
		enemy_->GetColorUsedForDrawing(), true);
}


//----------------------------------------------------
//敵の攻撃状態
void EnemyStateAttack::Init()
{
	angle = 0;
	bulletCoolTimer_ = kBulletCoolTime_;
	//radius_ = sqrt(pow(enemy_->GetPos().x - centerX, 2) + pow(enemy_->GetPos().y - centerY, 2)); // 初期位置から半径を計算

	//savePopPos_.x = enemy_->GetPos().x + cos(0) * kMoveCircleRadius_;
	//savePopPos_.y = enemy_->GetPos().y + sin(0) * kMoveCircleRadius_;

	moveSpeed_ = 3.0f;

	radianSpeed_ = moveSpeed_ * (3.14159f / 180.0f); // 度からラジアンに変換
	Vec2 pos = enemy_->GetPos();

	centerPos_.x = WINDOW_SIZE.x / 2; // 円の中心 x
	centerPos_.y = WINDOW_SIZE.y / 4; // 円の中心 y

	// 現在の位置から中心点への角度を計算
	angle = atan2(pos.y - centerPos_.y, pos.x - centerPos_.x);

	// 現在の位置と指定した半径の差を確認
	float dx = pos.x - centerPos_.x;
	float dy = pos.y - centerPos_.y;
	float currentDistance = sqrt(dx * dx + dy * dy);

	// 半径との差が小さければそのまま円運動を開始
	inTransition = (fabs(currentDistance - kMoveCircleRadius_) > 0.01f);
}

void EnemyStateAttack::Update()
{
	IEnemyState::Update();

	//enemy_->SetPos(enemy_->GetPos() + Vec2{ 0, Enemy::AUTO_MOVING_SPEED });

	//float radius = 100.0f; // 円の半径
	//float centerX = savePopPos_.x; // 円の中心 x
	//float centerY = savePopPos_.y; // 円の中心 y
	////float centerX = WINDOW_SIZE.x / 2; // 円の中心 x
	////float centerY = WINDOW_SIZE.y / 4; // 円の中心 y

	//const float PI = 3.14159f;
	//Vec2 pos;

	//angle += 2.5f;
	//angle = fmod(angle, 360.0f); // 360度を超えたらリセット

	////度数法の角度を弧度法に変換
	//float radians = angle * PI / 180.0f;
	////円運動の座標を計算
	//pos.x = savePopPos_.x + cos(radians) * radius;
	//pos.y = savePopPos_.y + sin(radians) * radius;

	//-----------------------
	Vec2 pos = enemy_->GetPos();

	if (inTransition) {
		// 円周上への移動処理
		
		float dx = pos.x - centerPos_.x;
		float dy = pos.y - centerPos_.y;
		float distance = sqrt(dx * dx + dy * dy);

		// 単位ベクトルを計算
		float ux = dx / distance;
		float uy = dy / distance;

		// 一定速度で円周上へ移動
		float distanceDifference = kMoveCircleRadius_ - distance;
		float moveStep = moveSpeed_;

		// 距離差が移動ステップより小さい場合は直接円周上に配置
		if (fabs(distanceDifference) <= moveStep) {
			pos.x = centerPos_.x + ux * kMoveCircleRadius_;
			pos.y = centerPos_.y + uy * kMoveCircleRadius_;
			inTransition = false; // 移動完了
		}
		else {
			// 円周上に向かって移動
			pos.x += ux * moveSpeed_ * (distanceDifference > 0 ? 1 : -1);
			pos.y += uy * moveSpeed_ * (distanceDifference > 0 ? 1 : -1);
		}

		// 角度を更新（移動に合わせて再計算）
		angle = atan2(pos.y - centerPos_.y, pos.x - centerPos_.x);
	}
	else {
		// 円運動の更新
		angle += radianSpeed_;
		if (angle > 3.14159f * 2) angle -= 3.14159f * 2; // 2πを超えたらリセット

		// 新しい位置を計算
		pos.x = centerPos_.x + cos(angle) * kMoveCircleRadius_;
		pos.y = centerPos_.y + sin(angle) * kMoveCircleRadius_;
	}

	//発射タイマーをカウントダウン
	bulletCoolTimer_--;
	//指定時間に達した
	if (bulletCoolTimer_ <= 0)
	{
		//弾を発射
		Fire();
		//発射タイマーを初期化
		bulletCoolTimer_ = kBulletCoolTime_;
	}

	enemy_->SetPos(pos);
}

void EnemyStateAttack::Draw()
{
	const Vec2 pos = enemy_->GetPos();

	const Vec2 TOP = pos + Vec2{ 0, -Enemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 RIGHT_BOTTOM = pos +
		Vec2{ Enemy::PROT_ENEMY_DRAWING_SIZE, Enemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 LEFT_BOTTOM = pos +
		Vec2{ -Enemy::PROT_ENEMY_DRAWING_SIZE, Enemy::PROT_ENEMY_DRAWING_SIZE };

	DrawTriangle(TOP.x, TOP.y, RIGHT_BOTTOM.x, RIGHT_BOTTOM.y, LEFT_BOTTOM.x, LEFT_BOTTOM.y,
		enemy_->GetColorUsedForDrawing(), true);
}

void EnemyStateAttack::Fire()
{
	//　弾の速度
	const float kBulletSpeed = -10.0f;
	Vec2 velocity(0, kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	//velocity = Root(velocity, rotation_);

	//弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(enemy_->GetPos(), velocity);

	//弾を登録する
	enemy_->GetBullets().push_back(std::move(newBullet));
}

