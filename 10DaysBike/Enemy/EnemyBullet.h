#pragma once

#include "IObject2D.h"
#include "CircleCollider.h"

class EnemyBullet : public IObject2D
{

public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize(const Vec2& position, const Vec2& velocity);
	void Init()override;
	void Update()override;

	//�Q�b�^�[
	bool IsDead() const { return isDead_; }

	//�`��
	void Draw()override;

	// �Փ˂����m������Ăяo�����R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info) override;

	void OnCollisionStop();

	//����
	void Dead();

	//���Z�b�g
	void Reset(Vec2 position);

	void SetDead() { isDead_ = true; };

	void SetGraph(int graph) { graph_ = graph; isDrawGraph_ = true; };
	

private:

	const float kBulletRadius_ = 5.0f;

	//��]�p
	float radian_;

	//���x
	Vec2 velocity_;

	float size_ = 5;

	//����
	static const int32_t kLifeTime = 60 * 5;

	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;

	bool canMoved;

	//�����������ǂ���
	bool isHit_ = false;

	bool markedForDeletion_ = false;

	int graph_ = 0;

	bool isDrawGraph_ = false;

	//�G�̃R���C�_�[
	std::unique_ptr<CircleCollider> bulletCollider_ = nullptr;

};