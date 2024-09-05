#include "Trajectory.h"

const ColorDxLib Trajectory::PROT_TRAJ_COLOR = { 255,255,0 };


void Trajectory::Init()
{
	const TwoPoses POSES = { {0,0},{0,0} };
	const Vec2 VEC = { 0,0 };

	Init(POSES, VEC);
}

void Trajectory::Init(const TwoPoses& twoPoses, const Vec2& vec, bool isHead)
{
	color_ = PROT_TRAJ_COLOR;

	twoPoses_ = twoPoses;
	vec_ = vec;
	isHead_ = isHead;
}

void Trajectory::Update()
{
	pos_ += vec_;

	twoPoses_.sPos += vec_;
	twoPoses_.ePos += vec_;

	if (GetIsOffingScreen(twoPoses_.sPos, twoPoses_.ePos))
	{
		//画面外に出たら消してもらうため
		isAlive_ = false;
	}
}

void Trajectory::Draw()
{
	const Vec2 S_POS = twoPoses_.sPos;
	const Vec2 E_POS = twoPoses_.ePos;

	//線描画
	DrawLine(S_POS.x, S_POS.y, E_POS.x, E_POS.y, GetColorUsedForDrawing(), LINE_TICKNESS);
}
