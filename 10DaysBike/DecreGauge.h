#pragma once
#include "Gauge.h"

//å∏Ç¡ÇΩÇ±Ç∆Ç™ÇÌÇ©ÇËÇ‚Ç∑Ç≠Ç∑ÇÈÇΩÇﬂÇÃÉQÅ[ÉW
class DecreGauge :
	public IGauge
{
public:
	static const ColorDxLib COLOR;
	static const float ALPHA;
private:
	Vec2 sWidthHeight_ = { 0,0 };
	Vec2 eWidthHeight_ = { 0,0 };
	uint16_t decreTimer_ = 0;
	uint16_t decreTimerTmp_ = 0;
	bool isDecreacing_ = false;


public:
	void Init()override;
	void Update()override;
	void Draw()override;
public:
	void StartDecreGauge( const Vec2& endWidthHeight, uint16_t time);
	void SetStartWH(const Vec2& wh) { sWidthHeight_ = wh; }
};

