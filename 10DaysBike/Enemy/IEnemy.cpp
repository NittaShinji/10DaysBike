#include "IEnemy.h"
#include "CollisionAttribute.h"
#include "Inform.h" 
#include "TrajectoriesManager.h"

const float IEnemy::AUTO_MOVING_SPEED = 3.0f;
const float IEnemy::SIDE_MOVING_SPEED = 3.0f;
const ColorDxLib IEnemy::PROT_ENEMY_COLOR = { 255,128,128 };
int IEnemy::explosionSoundHandle_;
int IEnemy::deadSoundHandle_;

IEnemy::~IEnemy()
{

}

void IEnemy::LoadSound()
{
	explosionSoundHandle_ = LoadSoundMem((RESOUCE_PATH + "enemyDamege.wav").c_str());
	deadSoundHandle_ = LoadSoundMem((RESOUCE_PATH + "enemyDead.wav").c_str());
}

void IEnemy::Init(){}

void IEnemy::Init(const Vec2& pos, std::string name)
{
	name_ = name;

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
	drawPos_ = pos_;
}

void IEnemy::Draw()
{	
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

		std::string objName = info.object->GetName();
		if (objName == TrajectoriesManager::UP_TRAJ_NAME)
		{
			hp_ -= 1;
		}
		else if (objName == TrajectoriesManager::BURST_DOWN_NAME)
		{
			hp_ = 0;
		}
		else if (objName == TrajectoriesManager::DOWN_TRAJ_NAME)
		{
			hp_ -= 1;
		}
		else if (objName == TrajectoriesManager::BURST_UP_NAME)
		{
			hp_ -= 2;
		}


		color_ = { 255,0,0 };

		//�_���[�W���ɃQ�[�W�񕜂�����
		chargeFunc_(DAMAGED_CHARGE_GAUGE_RATIO);
		//�_���[�W���o
		damagedEffectFunc_(pos_, radius_);
	}

	if (hp_ <= 0)
	{
		//�������Ă��Ȃ�������Đ�����
		if (CheckSoundMem(deadSoundHandle_) == 0)
		{
			PlaySoundMem(deadSoundHandle_, DX_PLAYTYPE_BACK);
		}
	}
	else {
		//�������Ă��Ȃ�������Đ�����
		if (CheckSoundMem(explosionSoundHandle_) == 0)
		{
			PlaySoundMem(explosionSoundHandle_, DX_PLAYTYPE_BACK);
		}
	}
}
