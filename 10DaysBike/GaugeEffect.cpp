#include "GaugeEffect.h"


void GaugeEffect::Generate()
{
	timer++;

	if (timer % interval_ == 0)
	{
		for (int i = 0; i < generateNum_; i++)
		{
			Vec2 genePos;
			genePos.x = pos_.x - widthHeight_.x / 2.0f + GetRand(widthHeight_.x);
			genePos.y = pos_.y - widthHeight_.y / 2.0f + GetRand(widthHeight_.y);

			Vec2 sVec;
			sVec.x = (float)(GetRand(dirXMax_ * 10.0f) - (dirXMax_ - dirXMin_) * 10.0f / 4.0f) / 10.0f;
			sVec.y = (float)(GetRand(dirYMax_ * 10.0f) - (dirYMax_ - dirYMin_) * 10.0f / 4.0f) / 10.0f;


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

