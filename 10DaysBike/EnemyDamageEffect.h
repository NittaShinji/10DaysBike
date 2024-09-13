#pragma once
#include "IEmitter.h"


class EnemyDamageEffect :
    public IEmitter
{
public:
	//�ō����x
	const float MAX_SPEED = 65.0f;
	//���a
	const float MAX_RADIUS = 6.0f;
	const int TIMER = 55;
	const int BLEND_MODE = DX_BLENDMODE_ALPHA;
	const int16_t BLEND_PARAM = 160;


private:

public:
	void Generate()override;
};

