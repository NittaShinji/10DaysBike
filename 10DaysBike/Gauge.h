#pragma once
#include"IObject2D.h"
#include"Inform.h"


//ƒQ[ƒW‚Ì’†‚Ì•”•ª
class Gauge : public IObject2D
{
public:
	static const ColorDxLib COLOR;
	static const ColorDxLib DANGER_COLOR;
private:
	Vec2 widthHeight_ = { 0,0 };
	float ratio_ = 0;


private:

public:
	void Init()override;
	void Update()override;
	void Draw()override;
public:
	void SetWidthHeight(const Vec2& widthHeight) { widthHeight_ = widthHeight; }
	void SetRatio(float ratio) { ratio_ = ratio; }
};

