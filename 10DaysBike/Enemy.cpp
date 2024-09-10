#include "Enemy.h"
#include "EnemyState.h"
#include "BulletManager.h"
#include "CollisionAttribute.h"
const float Enemy::AUTO_MOVING_SPEED = 3.0f;
const float Enemy::SIDE_MOVING_SPEED = 3.0f;
const ColorDxLib Enemy::PROT_ENEMY_COLOR = { 255,128,128 };

Enemy::~Enemy()
{
	bulletManager_ = nullptr;

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	//for (int i = 0; i < PROT_ENEMY_IMGAE_NUM; i++)
	//{
	//	DeleteGraph(graphHandle_[i]);
	//}

	DeleteGraph(graphHandle_);
}

void Enemy::MoveUpdate()
{
	
}

void Enemy::Init()
{
	Init({ 0,0 });
}

void Enemy::Init(const Vec2& pos)
{
	name_ = "enemy";

	pos_ = pos;

	color_ = PROT_ENEMY_COLOR;

	radius_ = PROT_ENEMY_DRAWING_SIZE;

	//trajManag_.reset();
	//trajManag_ = std::make_unique<TrajectoriesManager>();
	//trajManag_->Init(pos_);

	//�R���C�_�[�̒ǉ�
	const float radius = static_cast<float>(PROT_ENEMY_DRAWING_SIZE);
	enemyCollider_ = std::make_unique<CircleCollider>(pos_, radius);

	//�R���C�_�[�̓o�^
	SetCollider(enemyCollider_.get());

	//�������w��
	enemyCollider_->SetAttribute(COLLISION_ATTR_ENEMYS);

	ProccesingNewTrajs();

	//�摜�ǂݍ���
	graphHandle_ = LoadGraph((RESOUCE_PATH + "batEnemy.png").c_str());

	//LoadDivGraph((RESOUCE_PATH + "bulletFlyEnemy.png").c_str(), 4, 4, 1, 128, 128, graphHandle_);

	//�X�e�[�g
	ChangeState(std::make_unique<EnemyStateWait>());
}

void Enemy::Update()
{
	state_->Update();
	IEnemy::Update();
}

void Enemy::Draw()
{
	if (hp_ > 0) 
	{
		//state_->Draw();
	}
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw();
	}

	unsigned int Cr;
	// ���̐F�R�[�h��ۑ�
	Cr = GetColor(255, 255, 255);
	DrawFormatString(100, 300, Cr, "�GHP : %d", hp_);

	//DrawGraph(pos_.x - radius_, pos_.y - radius_, graphHandle_[0], FALSE);
	DrawGraph(pos_.x - radius_, pos_.y - radius_, graphHandle_, FALSE);
}

//----------------------------------------------------------------------
void Enemy::ChangeState(std::unique_ptr<IEnemyState> state)
{
	state_.reset();
	state_ = std::move(state);
	state_->SetEnemyPtr(this);
	state_->Init();
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	IEnemy::OnCollision(info);
}

void Enemy::ProccesingNewTrajs()
{
	//trajManag_->ProccesingTurning();
}
