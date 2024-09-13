#pragma once
#include "IObject2D.h"


class Particle :
    public IObject2D
{
public:
    enum struct ShapeType
    {
        CIRCLE,
        SQUARE,
        TRIANGLE,
    };

    struct ParticleInform
    {
        //â¡ë¨ìx
        Vec2 accel = { 0,0 };
        //ç≈çÇë¨ìx
        float maxSpeed = 1.0f;
        //îºåa
        float radius = 1.0f;

        int timer = 99999;

        int blendMode = DX_BLENDMODE_ALPHA;
        int16_t blendParam = 100;

        ShapeType type = ShapeType::CIRCLE;
    };

private:
    ParticleInform info_;

private:

public:
    void Init()override;
    void Init(const ParticleInform& info);
    void Update()override;
    void Draw()override;
};

