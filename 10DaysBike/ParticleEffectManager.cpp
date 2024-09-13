#include "ParticleEffectManager.h"

void ParticleEffectManager::Init()
{
	particles_.clear();
}

void ParticleEffectManager::Update()
{
	for (auto& particle : particles_)
	{
		particle->Update();
	}

	for (auto itr = particles_.begin(); itr != particles_.end(); itr++)
	{
		if (itr->get()->GetIsAlive() == false)
		{
			particles_.erase(itr);

			if (particles_.size())
			{
				itr = particles_.begin();
			}
			else
			{
				break;
			}
		}
	}
}

void ParticleEffectManager::Draw()
{
	for (auto& particle : particles_)
	{
		particle->Draw();
	}
}

void ParticleEffectManager::GenerateParticle(const Vec2& pos, const Vec2& sVec, const ColorDxLib& color, const Particle::ParticleInform& info)
{
	auto particle = std::make_unique<Particle>();

	particle->Init(info);
	particle->SetPos(pos);
	particle->SetVec(sVec);
	particle->SetColor(color);

	particles_.push_back(std::move(particle));
}
