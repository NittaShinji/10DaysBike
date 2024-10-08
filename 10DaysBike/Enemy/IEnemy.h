#pragma once
#include"IObject2D.h"
#include "CircleCollider.h"
#include "Inform.h"
#include "ExplosionStaging.h"
#include <list>
#include <functional>

class IEnemy : public IObject2D
{

public:
	static const float AUTO_MOVING_SPEED;
	static const float SIDE_MOVING_SPEED;
	static const uint16_t PROT_ENEMY_DRAWING_SIZE = 50;
	static const ColorDxLib PROT_ENEMY_COLOR;
	static const int TURN_KEY = KEY_INPUT_SPACE;

private:
	//1.0f==100%
	const float DAMAGED_CHARGE_GAUGE_RATIO = 0.05f / 60.0f;

protected:

	//死亡フラグ
	bool isDead_ = false;
	//当たったかどうか
	bool isHit_ = false;
	//ダメージをどれだけ受けるか
	uint16_t damageNum_ = 1;
	//敵のコライダー
	std::unique_ptr<CircleCollider> enemyCollider_ = nullptr;
	//HP
	const int32_t kDefaultEnemyHP_ = 30;
	int32_t hp_ = kDefaultEnemyHP_;
	//角度
	double angle_ = 0.0;
	//描画用座標
	Vec2 drawPos_;
	Vec2 size_ = { 1,1 };

	//爆発音
	static int explosionSoundHandle_;
	//死亡音
	static int deadSoundHandle_;

	//ゲージをチャージするための関数
	std::function<void(float chargeRatio)> chargeFunc_ = nullptr;
	//ダメージ演出するための関数
	std::function<void(const Vec2& pos, float radius)> damagedEffectFunc_ = nullptr;

public:
	~IEnemy();

public:

	static void LoadSound();
	static void UnloadSound() { DeleteSoundMem(explosionSoundHandle_); }

	void Init()override;
	virtual void Init(const Vec2& pos, std::string name);
	void Update()override;
	void Draw()override;

public:

	//コライダーの追加
	void AddCollider();

	//衝突時に呼び出される関数
	void OnCollision(const CollisionInfo& info) override;

public:
	int32_t GetEnemyHP() { return hp_; }
	bool GetIsDead() const { return isDead_; }

	void SetChargeGaugeFunc(const std::function<void(float chargeRatio)>& func) { chargeFunc_ = func; }
	void SetDamagedEffectFunc(const std::function<void(const Vec2& pos, float radius)>& func) { damagedEffectFunc_ = func; }
};

