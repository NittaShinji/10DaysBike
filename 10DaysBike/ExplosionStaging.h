#pragma once
#include "Vec2.h"
#include "ExplosionCircle.h"
#include <vector>
#include <memory>

class ExplosionStaging
{
public:

    static const int kIncreaseRadiusNum = 5;
    static const int kIncreaseAlphaNum = 5;

public:

    void Init(Vec2 pos, int numCircles);
    void Update(Vec2 pos);
    void Draw();

    // �G�̗h������i�������̂݁j
    void Shake(Vec2& enemyPos);

    // �������I�����Ă��邩�m�F
    bool IsFinished() {
        return !active;
    }

private:

    std::vector<std::unique_ptr<ExplosionCircle>> circles_;  // �~�̃��X�g
    bool active;                  // �������L�����ǂ���
};

