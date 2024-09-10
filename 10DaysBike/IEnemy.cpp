#include "IEnemy.h"
#include "CollisionAttribute.h"

IEnemy::~IEnemy()
{

}

void IEnemy::Init()
{
	Init({ 0,0 });
}

void IEnemy::Init(const Vec2& pos)
{
	name_ = "IEnemy";

	pos_ = pos;

	color_ = PROT_ENEMY_COLOR;

	radius_ = PROT_ENEMY_DRAWING_SIZE;
}

void IEnemy::Update()
{
	//�U�����󂯂�������Ȃ���(�������Ă����OnCollision�֐��ōēxtrue�ɂȂ�)
	if (isHit_ == true)
	{
		isHit_ = false;
		color_ = { 255,128,128 };
	}

	//HP��0�ɂȂ����玀�S��Ԃɂ��A�R���C�_�[�������t���O���I���ɂ���
	if (hp_ <= 0)
	{
		isDead_ = true;
		isDeleteCollider_ = true;
	}

	//���݈ʒu���R���C�_�[�p�̕ϐ��ɓn��
	coliderPos_ = pos_;
}

void IEnemy::Draw()
{
	if (hp_ > 0)
	{
		unsigned int Cr;
		// ���̐F�R�[�h��ۑ�
		Cr = GetColor(255, 255, 255);
		DrawFormatString(100, 300, Cr, "�GHP : %d", hp_);
	}
}

void IEnemy::AddCollider()
{
	//�R���C�_�[�̒ǉ�
	const float radius = static_cast<float>(PROT_ENEMY_DRAWING_SIZE);
	enemyCollider_ = std::make_unique<CircleCollider>(pos_, radius);

	//�R���C�_�[�̓o�^
	SetCollider(enemyCollider_.get());

	//�������w��
	enemyCollider_->SetAttribute(COLLISION_ATTR_ENEMYS);
}

void IEnemy::OnCollision(const CollisionInfo& info)
{
	if (isHit_ == false)
	{
		isHit_ = true;
		hp_ -= damageNum_;
		color_ = { 255,0,0 };
	}
}
