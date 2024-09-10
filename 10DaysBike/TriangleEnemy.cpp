#include "TriangleEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

TriangleEnemy::~TriangleEnemy()
{
	bulletManager_ = nullptr;
}

void TriangleEnemy::Init()
{
	Init({ 0,0 });
}

void TriangleEnemy::Init(const Vec2& pos)
{
	name_ = "enemy";

	pos_ = pos;

	color_ = PROT_ENEMY_COLOR;

	radius_ = PROT_ENEMY_DRAWING_SIZE;

	IEnemy::AddCollider();
}

void TriangleEnemy::Update()
{
	IEnemy::Update();

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
}

void TriangleEnemy::Draw()
{
	if (hp_ > 0)
	{
		// 円を描画
		const Vec2 BOTTOM = pos_ - Vec2{ 0, -radius_ };
		const Vec2 RIGHT_TOP = pos_ -
			Vec2{ radius_, radius_ };
		const Vec2 LEFT_TOP = pos_ -
			Vec2{ -radius_, radius_ };

		color_ = { 255,0,0 };

		DrawTriangle(BOTTOM.x, BOTTOM.y, RIGHT_TOP.x, RIGHT_TOP.y, LEFT_TOP.x, LEFT_TOP.y,
			GetColorUsedForDrawing(), true);
	}
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw();
	}

	unsigned int Cr;
	// 白の色コードを保存
	Cr = GetColor(255, 255, 255);
	DrawFormatString(100, 300, Cr, "敵HP : %d", hp_);
}

//----------------------------------------------------------------------

void TriangleEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

void TriangleEnemy::Fire()
{
	//　弾の速度
	const float kBulletSpeed = -10.0f;
	Vec2 velocity(0, kBulletSpeed);

	//弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(pos_, velocity);

	//弾を弾マネージャーに登録する
	bulletManager_->GetBullets().push_back(std::move(newBullet));
}
