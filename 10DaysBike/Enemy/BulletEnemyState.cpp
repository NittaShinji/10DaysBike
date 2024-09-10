#include "IBulletEnemy.h"
#include "BulletEnemyState.h"
#include "BulletManager.h"

//----------------------------------------------------
//���N���X

void IBulletEnemyState::Update()
{
}

//----------------------------------------------------
//�G�̑ҋ@���
void EnemyStateWait::Init()
{
}

void EnemyStateWait::Update()
{
	enemy_->SetPos(enemy_->GetPos());

	IBulletEnemyState::Update();

	if (waitTimer_ >= 0) 
	{
		waitTimer_--;
		if (waitTimer_ < 0)
		{
			enemy_->ChangeState(std::make_unique<EnemyStateCircleAttack>());
		}
	}
}

void EnemyStateWait::Draw()
{
	const Vec2 pos = enemy_->GetPos();

	const Vec2 BOTTOM = pos - Vec2{ 0, -IEnemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 RIGHT_TOP = pos -
		Vec2{ IEnemy::PROT_ENEMY_DRAWING_SIZE, IEnemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 LEFT_TOP = pos -
		Vec2{ -IEnemy::PROT_ENEMY_DRAWING_SIZE, IEnemy::PROT_ENEMY_DRAWING_SIZE };

	DrawTriangle(BOTTOM.x, BOTTOM.y, RIGHT_TOP.x, RIGHT_TOP.y, LEFT_TOP.x, LEFT_TOP.y,
		enemy_->GetColorUsedForDrawing(), true);
}


//----------------------------------------------------
//�G�̍U�����
void EnemyStateCircleAttack::Init()
{
	angle = 0;
	bulletCoolTimer_ = kBulletCoolTime_;

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

void EnemyStateCircleAttack::Update()
{
	IBulletEnemyState::Update();

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
		enemy_->Fire(enemy_->GetBulletSpeed());
		//���˃^�C�}�[��������
		bulletCoolTimer_ = kBulletCoolTime_;
	}

	enemy_->SetPos(pos);
}

void EnemyStateCircleAttack::Draw()
{
	const Vec2 pos = enemy_->GetPos();

	const Vec2 TOP = pos + Vec2{ 0, -IEnemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 RIGHT_BOTTOM = pos +
		Vec2{ IEnemy::PROT_ENEMY_DRAWING_SIZE, IEnemy::PROT_ENEMY_DRAWING_SIZE };
	const Vec2 LEFT_BOTTOM = pos +
		Vec2{ -IEnemy::PROT_ENEMY_DRAWING_SIZE, IEnemy::PROT_ENEMY_DRAWING_SIZE };

	DrawTriangle(TOP.x, TOP.y, RIGHT_BOTTOM.x, RIGHT_BOTTOM.y, LEFT_BOTTOM.x, LEFT_BOTTOM.y,
		enemy_->GetColorUsedForDrawing(), true);
}

void EnemyStateNonAction::Init(){}

void EnemyStateNonAction::Update(){}

void EnemyStateNonAction::Draw(){}

void EnemyStateFireBullet::Init()
{
	bulletCoolTimer_ = kBulletCoolTime_;
}

void EnemyStateFireBullet::Update()
{
	//���˃^�C�}�[���J�E���g�_�E��
	bulletCoolTimer_--;
	//�w�莞�ԂɒB����
	if (bulletCoolTimer_ <= 0)
	{
		//�e�𔭎�
		enemy_->Fire(enemy_->GetBulletSpeed());
		//���˃^�C�}�[��������
		bulletCoolTimer_ = kBulletCoolTime_;
	}
}

void EnemyStateFireBullet::Draw(){}

