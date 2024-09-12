#pragma once
#include "CollisionPrimitive.h"
#include "Vec2.h"

class ColliderManager;

class Collision
{
public:
    Collision();
    ~Collision();
    
    //�~�Ɖ~�̏Փ˔���
    static bool CheckCircle2Circle(const Circle& circleA, const Circle& circleB);

};
