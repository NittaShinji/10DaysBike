#include "GaugeEffect.h"


void GaugeEffect::Generate()
{
	if(TimerUpdate())
	{
		for (int i = 0; i < generateNum_; i++)
		{
			Vec2 genePos;
			genePos.x = pos_.x - widthHeight_.x / 2.0f + GetRand(widthHeight_.x);
			genePos.y = pos_.y - widthHeight_.y / 2.0f + GetRand(widthHeight_.y);

			Vec2 sVec = GetRandomVecFromDirMinMax();

			Particle::ParticleInform info = {
				ACCLEL_Y,
				MAX_SPEED,
				GetRand(MAX_RADIUS) * 10.0f /10.0f ,
				TIMER,
				BLEND_MODE,
				BLEND_PARAM,
				Particle::ShapeType::SQUARE
			};

			ParticleEffectManager::GetInstance().GenerateParticle(genePos, sVec, color_, info);
		}
	}
}

