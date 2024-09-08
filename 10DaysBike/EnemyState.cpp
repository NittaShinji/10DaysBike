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
	//radius_ = sqrt(pow(enemy_->GetPos().x - centerX, 2) + pow(enemy_->GetPos().y - centerY, 2)); // �����ʒu���甼�a���v�Z

	//savePopPos_.x = enemy_->GetPos().x + cos(0) * kMoveCircleRadius_;
	//savePopPos_.y = enemy_->GetPos().y + sin(0) * kMoveCircleRadius_;

	moveSpeed_ = 3.0f;

	radianSpeed_ = moveSpeed_ * (3.14159f / 180.0f); // �x���烉�W�A���ɕϊ�
	Vec2 pos = enemy_->GetPos();

	centerPos_.x = WINDOW_SIZE.x / 2; // �~�̒��S x
	centerPos_.y = WINDOW_SIZE.y / 4; // �~�̒��S y

	// ���݂̈ʒu���璆�S�_�ւ̊p�x���v�Z
	angle = atan2(pos.y - centerPos_.y, pos.x - centerPos_.x);

	// ���݂̈ʒu�Ǝw�肵�����a�̍����m�F
	float dx = pos.x - centerPos_.x;
	float dy = pos.y - centerPos_.y;
	float currentDistance = sqrt(dx * dx + dy * dy);

	// ���a�Ƃ̍�����������΂��̂܂܉~�^�����J�n
	inTransition = (fabs(currentDistance - kMoveCircleRadius_) > 0.01f);
}

void EnemyStateAttack::Update()
{
	IEnemyState::Update();

	//enemy_->SetPos(enemy_->GetPos() + Vec2{ 0, Enemy::AUTO_MOVING_SPEED });

	//float radius = 100.0f; // �~�̔��a
	//float centerX = savePopPos_.x; // �~�̒��S x
	//float centerY = savePopPos_.y; // �~�̒��S y
	////float centerX = WINDOW_SIZE.x / 2; // �~�̒��S x
	////float centerY = WINDOW_SIZE.y / 4; // �~�̒��S y

	//const float PI = 3.14159f;
	//Vec2 pos;

	//angle += 2.5f;
	//angle = fmod(angle, 360.0f); // 360�x�𒴂����烊�Z�b�g

	////�x���@�̊p�x���ʓx�@�ɕϊ�
	//float radians = angle * PI / 180.0f;
	////�~�^���̍��W���v�Z
	//pos.x = savePopPos_.x + cos(radians) * radius;
	//pos.y = savePopPos_.y + sin(radians) * radius;

	//-----------------------
	Vec2 pos = enemy_->GetPos();

	if (inTransition) {
		// �~����ւ̈ړ�����
		
		float dx = pos.x - centerPos_.x;
		float dy = pos.y - centerPos_.y;
		float distance = sqrt(dx * dx + dy * dy);

		// �P�ʃx�N�g�����v�Z
		float ux = dx / distance;
		float uy = dy / distance;

		// ��葬�x�ŉ~����ֈړ�
		float distanceDifference = kMoveCircleRadius_ - distance;
		float moveStep = moveSpeed_;

		// ���������ړ��X�e�b�v��菬�����ꍇ�͒��ډ~����ɔz�u
		if (fabs(distanceDifference) <= moveStep) {
			pos.x = centerPos_.x + ux * kMoveCircleRadius_;
			pos.y = centerPos_.y + uy * kMoveCircleRadius_;
			inTransition = false; // �ړ�����
		}
		else {
			// �~����Ɍ������Ĉړ�
			pos.x += ux * moveSpeed_ * (distanceDifference > 0 ? 1 : -1);
			pos.y += uy * moveSpeed_ * (distanceDifference > 0 ? 1 : -1);
		}

		// �p�x���X�V�i�ړ��ɍ��킹�čČv�Z�j
		angle = atan2(pos.y - centerPos_.y, pos.x - centerPos_.x);
	}
	else {
		// �~�^���̍X�V
		angle += radianSpeed_;
		if (angle > 3.14159f * 2) angle -= 3.14159f * 2; // 2�΂𒴂����烊�Z�b�g

		// �V�����ʒu���v�Z
		pos.x = centerPos_.x + cos(angle) * kMoveCircleRadius_;
		pos.y = centerPos_.y + sin(angle) * kMoveCircleRadius_;
	}

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

