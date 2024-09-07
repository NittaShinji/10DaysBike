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
}

void EnemyStateAttack::Update()
{
	enemy_->SetPos(enemy_->GetPos() + Vec2{ 0, Enemy::AUTO_MOVING_SPEED });

	IEnemyState::Update();

	float radius = 100.0f; // 円の半径
	float centerX = WINDOW_SIZE.x / 2; // 円の中心 x
	float centerY = WINDOW_SIZE.y / 4; // 円の中心 y
	const float PI = 3.14159f;
	Vec2 pos;

	angle += 2.5f;
	angle = fmod(angle, 360.0f); // 360度を超えたらリセット

	//度数法の角度を弧度法に変換
	float radians = angle * PI / 180.0f;
	//円運動の座標を計算
	pos.x = centerX + cos(radians) * radius;
	pos.y = centerY + sin(radians) * radius;

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

