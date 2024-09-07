#pragma once
#include"IObject2D.h"
#include "CircleCollider.h"

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
	static const uint8_t LINE_TICKNESS = 15;
	static const uint8_t LIFE_FRAME = 70;
	static const ColorDxLib PROT_TRAJ_COLOR;
	static const uint16_t ALPHA_MAX = 255;
	static const uint8_t SHAKING_LENGTH = 3;

private:
	TwoPoses twoPoses_;
	bool isHead_ = false;
	std::unique_ptr<CircleCollider> trajectoryCollider_ = nullptr;
	uint16_t lifeFrame_ = LIFE_FRAME;
	Vec2 scrollVec_ = { 0,0 };

private:

public:
	Trajectory();
	~Trajectory();
	void Init()override;
	void Init(const TwoPoses& twoPoses, const Vec2& vec, bool isHead = false);
	void Update()override;
	void Draw()override;

public:
	void SetTwoPoses(const Vec2& sPos, const Vec2& ePos) { twoPoses_ = TwoPoses{ sPos, ePos }; }
	void SetScrollVec(const Vec2& vec) { scrollVec_ = vec; }

	const TwoPoses& GetTwoPoses() { return twoPoses_; }
	bool GetIsHead() { return isHead_; }
};

