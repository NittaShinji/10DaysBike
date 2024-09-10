#pragma once
#include"IObject2D.h"
#include "CircleCollider.h"
#include <list>

class IEnemy : public IObject2D
{

public:
	static const float AUTO_MOVING_SPEED;
	static const float SIDE_MOVING_SPEED;
	static const uint16_t PROT_ENEMY_DRAWING_SIZE = 40;
	static const ColorDxLib PROT_ENEMY_COLOR;
	static const int TURN_KEY = KEY_INPUT_SPACE;

protected:

	//���S�t���O
	bool isDead_ = false;
	//�����������ǂ���
	bool isHit_ = false;
	//�_���[�W���ǂꂾ���󂯂邩
	uint16_t damageNum_ = 1;
	//�G�̃R���C�_�[
	std::unique_ptr<CircleCollider> enemyCollider_ = nullptr;
	//HP
	const int32_t kDefaultEnemyHP_ = 30;
	int32_t hp_ = kDefaultEnemyHP_;

public:
	~IEnemy();

public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;

public:

	//�R���C�_�[�̒ǉ�
	void AddCollider();

	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;

public:
	int32_t GetEnemyHP() { return hp_; }
	bool IsDead() const { return isDead_; }

};

