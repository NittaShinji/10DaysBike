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

public:
	void Init()override;
	void Update()override;
	void Draw()override;

};

//�U�����
class EnemyStateAttack : public IEnemyState
{

private:

public:
	void Init()override;
	void Update()override;
	void Draw()override;

};
