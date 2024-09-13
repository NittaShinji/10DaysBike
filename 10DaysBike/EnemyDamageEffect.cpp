#include "EnemyDamageEffect.h"

void EnemyDamageEffect::Generate()
{
	if (TimerUpdate())
	{
		for (int i = 0; i < generateNum_; i++)
		{
			Vec2 genePos;
			genePos.x = pos_.x + GetRand(radius_) - radius_ / 2.0f;
			genePos.y = pos_.y + GetRand(radius_) - radius_ / 2.0f;

			Vec2 sVec = GetRandomVecFromDirMinMax();

			Vec2 accel = -sVec / (float)TIMER;


			Particle::ParticleInform info = {
				accel,
				MAX_SPEED,
				GetRand(MAX_RADIUS) * 10.0f / 10.0f ,
				TIMER,
				BLEND_MODE,
				BLEND_PARAM,
				Particle::ShapeType::SQUARE
			};

			ParticleEffectManager::GetInstance().GenerateParticle(genePos, sVec, color_, info);
		}
	}
}
