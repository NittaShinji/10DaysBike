#pragma once
#include"IObject2D.h"
#include "CircleCollider.h"
#include "Inform.h"
#include "ExplosionStaging.h"
#include <list>

class IEnemy : public IObject2D
{

public:
	static const float AUTO_MOVING_SPEED;
	static const float SIDE_MOVING_SPEED;
	static const uint16_t PROT_ENEMY_DRAWING_SIZE = 50;
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
	//�������o
	std::unique_ptr<ExplosionStaging> ExplosionStaging_ = nullptr;
	//HP
	const int32_t kDefaultEnemyHP_ = 30;
	int32_t hp_ = kDefaultEnemyHP_;
	//�p�x
	double angle_ = 0.0;
	//�`��p���W
	Vec2 drawPos_;
	Vec2 size_ = { 1,1 };

	//������
	static int explosionSoundHandle_;
	//���S��
	static int deadSoundHandle_;

public:
	~IEnemy();

public:

	static void LoadSound();
	static void UnloadSound(){DeleteSoundMem(explosionSoundHandle_);}

	void Init()override;
	virtual void Init(const Vec2& pos, std::string name);
	void Update()override;
	void Draw()override;

public:

	//�R���C�_�[�̒ǉ�
	void AddCollider();

	//�Փˎ��ɌĂяo�����֐�
	void OnCollision(const CollisionInfo& info) override;

public:
	int32_t GetEnemyHP() { return hp_; }
	bool GetIsDead() const { return isDead_; }

};

