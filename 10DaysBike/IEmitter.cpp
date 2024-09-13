#include "IEmitter.h"

void IEmitter::Init(int interval, int generateNum, const Vec2& dirXMinMax, const Vec2& dirYMinMax)
{
	SetInterval(interval);
	SetGenerateNum(generateNum);

	SetDirXMinMax({ dirXMinMax });
	SetDirYMinMax({ dirYMinMax });
}

bool IEmitter::TimerUpdate()
{
	timer_++;

	if (timer_ % interval_ == 0)
	{
		return true;
	}

	return false;
}

Vec2 IEmitter::GetRandomVecFromDirMinMax()
{
	Vec2 sVec;
	sVec.x = (float)(GetRand(dirXMax_ * 10.0f) - (dirXMax_ - dirXMin_) * 10.0f / 4.0f) / 10.0f;
	sVec.y = (float)(GetRand(dirYMax_ * 10.0f) - (dirYMax_ - dirYMin_) * 10.0f / 4.0f) / 10.0f;

	return Vec2(sVec);
}
