#pragma once
#include"Particle.h"
#include<vector>

//
class ParticleEffectManager
{
public:
	std::vector<std::unique_ptr<Particle>> particles_;

private:


public:
	static ParticleEffectManager& GetInstance() { static ParticleEffectManager ins; return ins; }

	void Init();
	void Update();
	void Draw();

private:
	
public:
	void GenerateParticle(const Vec2& pos, const Vec2& sVec, const ColorDxLib& color, const Particle::ParticleInform& info);
};

