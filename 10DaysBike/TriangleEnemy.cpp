#include "TriangleEnemy.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"

const double TriangleEnemy::kBulletFlyEnemyImageScale_ = 1.0f;

TriangleEnemy::~TriangleEnemy()
{
	bulletManager_ = nullptr;

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	for (int i = 0; i < kBulletFlyEnemyImageNum_; i++)
	{
		DeleteGraph(graphHandle_[i]);
	}
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

	hp_ = 300;

	//�摜�ǂݍ���
	LoadDivGraph((RESOUCE_PATH + "bulletFlyEnemy.png").c_str(), 4, 4, 1, 128, 128, graphHandle_);

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
		//const Vec2 BOTTOM = pos_ - Vec2{ 0, -radius_ };
		//const Vec2 RIGHT_TOP = pos_ -
		//	Vec2{ radius_, radius_ };
		//const Vec2 LEFT_TOP = pos_ -
		//	Vec2{ -radius_, radius_ };

		//color_ = { 255,0,0 };

		//DrawTriangle(BOTTOM.x, BOTTOM.y, RIGHT_TOP.x, RIGHT_TOP.y, LEFT_TOP.x, LEFT_TOP.y,
		//	GetColorUsedForDrawing(), true);

		//�摜�ǂݍ���
		//DrawGraph(pos_.x - radius_, pos_.y - radius_, graphHandle_[0], FALSE);
		const int* handles = nullptr;
		DrawRotaGraph(pos_.x, pos_.y, kBulletFlyEnemyImageScale_, angle_, graphHandle_[0], TRUE, FALSE);
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw();
	}

	unsigned int Cr;
	// ���̐F�R�[�h��ۑ�
	Cr = GetColor(255, 255, 255);
	DrawFormatString(100, 320, Cr, "circle�GHP : %d", hp_);
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
