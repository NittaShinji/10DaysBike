#pragma once
#include"IObject2D.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include "EnemyBullet.h"
#include <list>

//�O���錾
class IEnemyState;

//�G
class Enemy : public IObject2D
{
public:
	static const float AUTO_MOVING_SPEED;
	static const float SIDE_MOVING_SPEED;
	static const uint16_t PROT_ENEMY_DRAWING_SIZE = 40;
	static const ColorDxLib PROT_ENEMY_COLOR;
	static const int TURN_KEY = KEY_INPUT_SPACE;
private:
	//�O�Ղ̊Ǘ��N���X
	//std::unique_ptr<TrajectoriesManager> trajManag_ = nullptr;
	//�X�e�[�g
	std::unique_ptr<IEnemyState>state_ = nullptr;
	//���S�t���O
	bool isDead_ = false;
	//�����������ǂ���
	bool isHit_ = false;
	//�G�̃R���C�_�[
	std::unique_ptr<CircleCollider> enemyCollider_ = nullptr;
	//�G�̒e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//HP
	const int32_t kDefaultEnemyHP_ = 30;
	int32_t hp_ = kDefaultEnemyHP_;

public:
	~Enemy() { bullets_.clear(); }
	
private:
	void MoveUpdate();
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:
	void ChangeState(std::unique_ptr<IEnemyState> state);
	void ProccesingTurning();
	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;

public:
	int32_t GetEnemyHP() { return hp_; }
	bool IsDead() const { return isDead_; }
	std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; };
};

