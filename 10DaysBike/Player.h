#pragma once
#include"IObject2D.h"
#include "CircleCollider.h"
#include"TrajectoriesManager.h"
#include<functional>
#include"Shake.h"

//前方宣言
class IPlayerState;

//プレイヤー
class Player : public IObject2D
{
public:
	static const float AUTO_MOVING_SPEED;
	static const float SIDE_MOVING_SPEED;
	static const uint16_t PROT_PLAYER_DRAWING_SIZE = 40;
	static const ColorDxLib PROT_PLAYER_COLOR;
	static const ColorDxLib DAMAGED_PLAYER_COLOR;
	static const int BURST_KEY = KEY_INPUT_SPACE;
	static const float DAMAGE_DECRE_RATIO;
public:
	//画像の種類
	enum struct ImageIndex
	{
		RUN,
		CURVE,
	};
	//傾きの時の
	enum struct CurveImageIndex
	{
		NORMAL,
		INCLI1,
		INCLI2,
	};

	static const uint16_t IMAGE_SIZE = 256;
	static const float IMAGE_EXTEND;

	static const std::string NORMAL_IMAGE_NAME;
	static const std::string CURVE_IMAGE_NAME;
	static const float DOWN_IMAGE_ANGLE;

	static const int CURVE_ANIME_INTERVAL = 5;
	static const int NORMAL_ANIME_INTERVAL = 8;

private:
	static const uint8_t NORMAL_IMAGE_NUM = 3;
	static const uint8_t CURVE_IMAGE_NUM = 3;
private:
	static const std::string UP_BURST_SOUND_NAME;
	static const std::string DOWN_BURST_SOUND_NAME;

private:
	//軌跡の管理クラス
	std::unique_ptr<TrajectoriesManager> trajManag_ = nullptr;
	//ステート
	std::unique_ptr<IPlayerState>state_ = nullptr;
	//プレイヤーのコライダー
	std::unique_ptr<CircleCollider> playerCollider_ = nullptr;
	//当たったかどうか
	bool isHit_ = false;
	//移動スピードの倍率(バースト用に)
	float moveSpeedRate_ = 1.0f;

	//雑に
	static const int DAMAGED_TIME = 70;
	static const int DAMAGED_SHAKE_MAX = 16;
	std::unique_ptr<Shake> damagedShake_ = nullptr;

	int normalImageHandles_[NORMAL_IMAGE_NUM];
	int curveImageHandles_[CURVE_IMAGE_NUM];
	uint8_t imageIndex_ = 0;

	//ダメージ受けたとき呼び出す関数
	std::function<bool(float damageDecreRatio)> damageFunc_ = nullptr;

	//音
	int downBurstSound_ = 0;
	int upBurstSound_ = 0;

public:
	~Player();
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Update(std::function<bool(float decreGauge,int32_t continueNum)>shootGaugeFunc,
		std::function<bool(float trajPos, float chargeGaugeRatio)> chargeGaugeFunc,
		float rimitY);
	void Draw()override;
	void DrawImage(const std::string& imageName, float angle, bool imageSideTurn);
public:
	void ChangeState(std::unique_ptr<IPlayerState> state);
	void ProccesingNewTrajs();
	void TrajManagerPosUpdate();
public:
	void SetMoveSpeedRate(float rate) { moveSpeedRate_ = rate; }
	void SetDamagedFunc(const std::function<float(float damageDecreRatio)>& func) { damageFunc_ = func; }

	float GetMoveSpeedRate() { return moveSpeedRate_; }
	Vec2 GetDrawPos();
public:
	void  IncrementImageIndex(const std::string& imageName);
	void  ImageIndexReset() { imageIndex_ = 0; }
	Vec2* GetPlayerPosPtr() { return &pos_; };
	IPlayerState* GetPlayerState() { return state_.get(); }

public:
	void PlayUpBurstSound();
	void StopUpBurstSound();
	void PlayDownBurstSound();

public:
	//衝突時に呼び出される関数
	void OnCollision(const CollisionInfo& info) override;
};

