#pragma once

//�O���錾
class Enemy;

//�G�̃X�e�[�g�̊��N���X
class IEnemyState
{
protected:
	Enemy* enemy_ = nullptr;

public:
	void SetEnemyPtr(Enemy* enemy) { enemy_ = enemy; }

public:
	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw() = 0;
};

//�ҋ@���
class EnemyStateWait : public IEnemyState
{

private:
	const float kWaitTime_ = 20.0f;
	float waitTimer_ = kWaitTime_;

public:
	void Init()override;
	void Update()override;
	void Draw()override;

};

//�U�����
class EnemyStateAttack : public IEnemyState
{

private:
	const float kAttackTime_ = 120.0f;
	const float kMoveCircleRadius_ = 100.0f;

	float attackTimer_ = kAttackTime_;
	//���S����̊p�x
	float angle = 0.0f;
	//�~�^���̑��x
	const float circleMoveSpeed = 0.35f;
	//���˃^�C�}�[
	int32_t bulletCoolTimer_;
	//���ˎ���
	const float kBulletCoolTime_ = 60.0f;
	//�o���ʒu��ۑ�
	Vec2 savePopPos_;
	//���S�_
	Vec2 centerPos_;
	// �~����ւ̈ړ������ǂ���
	bool inTransition; 
	//�ړ����x
	float moveSpeed_;
	//�p���x
	float radianSpeed_;

public:
	void Init()override;
	void Update()override;
	void Draw()override;

public:
	void Fire();

};
