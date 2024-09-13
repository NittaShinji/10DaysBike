#include "IEmitter.h"

void IEmitter::Init(int interval, int generateNum, const Vec2& dirXMinMax, const Vec2& dirYMinMax)
{
	SetInterval(interval);
	SetGenerateNum(generateNum);

	SetDirXMinMax({ dirXMinMax });
	SetDirYMinMax({ dirYMinMax });
}
