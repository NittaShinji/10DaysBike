#pragma once
#include "IObject2D.h"


class GaugeFrame :
	public IObject2D
{
public:
	static const ColorDxLib COLOR;
private:
	Vec2 widthHeight_ = { 0,0 };
	float thickness_ = 1.0f;


private:

public:
	void Init()override;
	void Update()override;
	void Draw()override;
public:
	void SetWidthHeight(const Vec2& widthHeight) { widthHeight_ = widthHeight; }
	const Vec2& GetWidthHeight() {return widthHeight_; }
	void SetThickness(float thickness) { thickness_ = thickness; }
};

