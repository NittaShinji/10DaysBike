#pragma once
#include"IObject2D.h"

//前方宣言
class IEnemyState;

//プレイヤー
class Enemy : public IObject2D
{
public:
	static const float AUTO_MOVING_SPEED;
	static const float SIDE_MOVING_SPEED;
	static const uint16_t PROT_ENEMY_DRAWING_SIZE = 40;
	static const ColorDxLib PROT_ENEMY_COLOR;
	static const int TURN_KEY = KEY_INPUT_SPACE;
private:

	//ステート
	std::unique_ptr<IEnemyState>state_ = nullptr;
	//死亡フラグ
	bool isDead_ = false;

private:
	void MoveUpdate();
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:
	void ChangeState(std::unique_ptr<IEnemyState> state);
};

