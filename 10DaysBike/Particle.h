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
        //加速度
        Vec2 accel = { 0,0 };
        //最高速度
        float maxSpeed = 1.0f;
        //半径
        float radius = 1.0f;

        int timer = 99999;

        int blendMode = DX_BLENDMODE_ALPHA;
        int16_t blendParam = 100;

        ShapeType type = ShapeType::CIRCLE;
    };

private:
    ParticleInform info_;
    float radiusTmp_ = 1.0f;
    int timerTmp_ = 1.0f;

private:

public:
    void Init()override;
    void Init(const ParticleInform& info);
    void Update()override;
    void Draw()override;
};

