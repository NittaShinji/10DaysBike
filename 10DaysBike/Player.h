#pragma once
#include"IObject2D.h"
#include"TrajectoriesManager.h"

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
	static const int TURN_KEY = KEY_INPUT_SPACE;
private:
	//軌跡の管理クラス
	std::unique_ptr<TrajectoriesManager> trajManag_ = nullptr;
	//ステート
	std::unique_ptr<IPlayerState>state_ = nullptr;

private:
	void MoveUpdate();
public:
	void Init()override;
	void Init(const Vec2& pos);
	void Update()override;
	void Draw()override;
public:
	void ChangeState(std::unique_ptr<IPlayerState> state);
	void ProccesingTurning();
};

