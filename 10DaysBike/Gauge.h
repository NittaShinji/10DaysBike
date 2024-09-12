#pragma once
#include"IObject2D.h"
#include"Inform.h"


//ÉQÅ[ÉWÇÃíÜÇÃïîï™
class IGauge : public IObject2D
{
private:
	static const ColorDxLib COLOR;
	static const ColorDxLib DANGER_COLOR;
protected:
	Vec2 widthHeight_ = { 0,0 };
	float colorRatio_ = 0;


protected:
	void DrawProcess();
public:
	virtual void Init()override;
	virtual void Update()override;
	virtual void Draw()override;
public:
	void SetWidthHeight(const Vec2& widthHeight) { widthHeight_ = widthHeight; }
	void SetColorRatio(float ratio) { colorRatio_ = ratio; }
};

