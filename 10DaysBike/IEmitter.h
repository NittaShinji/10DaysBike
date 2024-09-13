#pragma once
#include"IObject2D.h"
#include"ParticleEffectManager.h"

class IEmitter : public IObject2D
{
protected:
	int interval_ = 1;
	int generateNum_ = 1;

	float dirXMin_ = 0;
	float dirXMax_ = 0;
	float dirYMin_ = 0;
	float dirYMax_ = 0;

	int timer_ = 0;

public:
	void Init()override { ; }
	void Init(int interval, int generateNum, const Vec2& dirXMinMax, const Vec2& dirYMinMax);
	void Update()override { ; }
	void Draw()override { ; }

	bool TimerUpdate();

	virtual void Generate() = 0;

protected:
	Vec2 GetRandomVecFromDirMinMax();

protected:
	void SetInterval(int interval) { interval_ = interval; }
	void SetGenerateNum(int num) { generateNum_ = num; }

	void SetDirXMinMax(const Vec2& minMax) { dirXMin_ = minMax.x; dirXMax_ = minMax.y; }
	void SetDirYMinMax(const Vec2& minMax) { dirYMin_ = minMax.x; dirYMax_ = minMax.y; }
};

