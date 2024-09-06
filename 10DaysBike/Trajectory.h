#pragma once
#include"IObject2D.h"

//ãOê’ÇÃ1Ç¬
class Trajectory : public IObject2D
{
public:
	struct TwoPoses
	{
		Vec2 sPos = { 0,0 };
		Vec2 ePos = { 0,0 };
	};

public:
	static const uint8_t LINE_TICKNESS = 3;
	static const ColorDxLib PROT_TRAJ_COLOR;

private:
	TwoPoses twoPoses_;
	bool isHead_ = false;

private:

public:
	void Init()override;
	void Init(const TwoPoses& twoPoses, const Vec2& vec, bool isHead = false);
	void Update()override;
	void Draw()override;

public:
	void SetTwoPoses(const Vec2& sPos, const Vec2& ePos) { twoPoses_ = TwoPoses{ sPos, ePos }; }

	const TwoPoses& GetTwoPoses() { return twoPoses_; }
	bool GetIsHead() { return isHead_; }
};

