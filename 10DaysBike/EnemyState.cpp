#include "Enemy.h"
#include "EnemyState.h"

//----------------------------------------------------
//���N���X
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
//�G�̑ҋ@���
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
//�G�̍U�����
void EnemyStateAttack::Init()
{
	angle = 0;
	bulletCoolTimer_ = kBulletCoolTime_;
}

void EnemyStateAttack::Update()
{
	enemy_->SetPos(enemy_->GetPos() + Vec2{ 0, Enemy::AUTO_MOVING_SPEED });

	IEnemyState::Update();

	float radius = 100.0f; // �~�̔��a
	float centerX = WINDOW_SIZE.x / 2; // �~�̒��S x
	float centerY = WINDOW_SIZE.y / 4; // �~�̒��S y
	const float PI = 3.14159f;
	Vec2 pos;

	angle += 2.5f;
	angle = fmod(angle, 360.0f); // 360�x�𒴂����烊�Z�b�g

	//�x���@�̊p�x���ʓx�@�ɕϊ�
	float radians = angle * PI / 180.0f;
	//�~�^���̍��W���v�Z
	pos.x = centerX + cos(radians) * radius;
	pos.y = centerY + sin(radians) * radius;

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
	//�@�e�̑��x
	const float kBulletSpeed = -10.0f;
	Vec2 velocity(0, kBulletSpeed);

	// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
	//velocity = Root(velocity, rotation_);

	//�e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(enemy_->GetPos(), velocity);

	//�e��o�^����
	enemy_->GetBullets().push_back(std::move(newBullet));
}

