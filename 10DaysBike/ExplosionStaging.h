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

    // 敵の揺れを作る（爆発中のみ）
    void Shake(Vec2& enemyPos);

    // 爆発が終了しているか確認
    bool IsFinished() {
        return !active;
    }

private:

    std::vector<std::unique_ptr<ExplosionCircle>> circles_;  // 円のリスト
    bool active;                  // 爆発が有効かどうか
};

