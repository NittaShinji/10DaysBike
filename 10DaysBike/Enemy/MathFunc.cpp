#include "MathFunc.h"
#include<math.h>

float MathFunc::DeltaAngle(float angle1, float angle2)
{
    float delta = fmod(angle2 - angle1, 360.0f);
    if (delta > 180.0f) {
        delta -= 360.0f;
    }
    else if (delta < -180.0f) {
        delta += 360.0f;
    }
    return delta;
}

Vec2 MathFunc::AngleToVector(float angleInDegrees)
{
    float angleInRadians = angleInDegrees * DEG_TO_RAD; // �p�x�����W�A���ɕϊ�
    Vec2 unitVector;
    unitVector.x = cosf(angleInRadians); // cos(�p�x)��x����
    unitVector.y = sinf(angleInRadians); // sin(�p�x)��y����
    return unitVector;
}
