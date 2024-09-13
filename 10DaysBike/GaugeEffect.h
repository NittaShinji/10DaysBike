#pragma once
#include "IObject2D.h"
#include"IEmitter.h"
#include"IEmitter.h"

class GaugeEffect :
	public IEmitter
{
public:
	//â¡ë¨ìx
	const Vec2 ACCLEL_Y = { 0, 0.2f };
	//ç≈çÇë¨ìx
	const float MAX_SPEED = 25.0f;
	//îºåa
	const float MAX_RADIUS =5.0f;
	const int TIMER = 90;
	const int BLEND_MODE = DX_BLENDMODE_ALPHA;
	const int16_t BLEND_PARAM = 105;

private:
	Vec2 widthHeight_;

public:



private:

public:
	void Generate()override;

public:
	void SetWidthHeight(const Vec2& wh) { widthHeight_ = wh; }
};

