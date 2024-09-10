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

	//���˃^�C�}�[���J�E���g�_�E��
	bulletCoolTimer_--;
	//�w�莞�ԂɒB����
	if (bulletCoolTimer_ <= 0)
	{
		//�e�𔭎�
		Fire();
		//���˃^�C�}�[��������
		bulletCoolTimer_ = kBulletCoolTime_;
	}
}

void TriangleEnemy::Draw()
{
	if (hp_ > 0)
	{
		// �~��`��
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
	// ���̐F�R�[�h��ۑ�
	Cr = GetColor(255, 255, 255);
	DrawFormatString(100, 300, Cr, "�GHP : %d", hp_);
}

//----------------------------------------------------------------------

void TriangleEnemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

void TriangleEnemy::Fire()
{
	//�@�e�̑��x
	const float kBulletSpeed = -10.0f;
	Vec2 velocity(0, kBulletSpeed);

	//�e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(pos_, velocity);

	//�e��e�}�l�[�W���[�ɓo�^����
	bulletManager_->GetBullets().push_back(std::move(newBullet));
}
