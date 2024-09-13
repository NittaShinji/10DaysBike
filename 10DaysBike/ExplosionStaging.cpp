#include "ExplosionStaging.h"
#include "DxLib.h"

void ExplosionStaging::Init(Vec2 pos,int numCircles)
{
    //circles.clear();  // 既存の円をクリア
    //for (int i = 0; i < numCircles; ++i) {
    //    int randomX = pos.x + (rand() % 41 - 20); // 中心位置から±20の範囲でランダムな位置
    //    int randomY = pos.y + (rand() % 41 - 20);
    //    int maxR = rand() % 50 + 30;  // ランダムな最大半径 (30 - 80)
    //    circles.emplace_back(Vec2(randomX,randomY), maxR);  // 新しい円を追加
    //}

    int randomX = pos.x + (rand() % 41 - 20); // 中心位置から±20の範囲でランダムな位置
    int randomY = pos.y + (rand() % 41 - 20);
    int maxR = rand() % 50 + 30;  // ランダムな最大半径 (30 - 80)

    //弾を生成し、初期化
    std::unique_ptr<ExplosionCircle> newCircle = std::make_unique<ExplosionCircle>();
    newCircle->Init(Vec2(randomX,randomY), maxR);

    //弾を弾マネージャーに登録する
    circles_.push_back(std::move(newCircle));

    active = true;
}
void ExplosionStaging::Update(Vec2 pos)
{
    if (active) {
        bool allFinished = true;
        for (auto& circle : circles_) {
            circle->Update(pos);
            if (!circle->IsFinished()) {
                allFinished = false;
            }
        }
        if (allFinished) {
            active = false;  // 全ての円が終了したら爆発を終了
        }
    }
}

void ExplosionStaging::Draw()
{
    if (active) {
        for (auto& circle : circles_) {
            circle->Draw();
        }
    }

    //DrawCircle(pos_.x, pos_.y, radius, GetColor(255, 100, 0), TRUE);  // 円を描画
}

void ExplosionStaging::Shake(Vec2& enemyPos)
{
    if (active) {
        //enemyPos.x += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // ランダムに震える
        //enemyPos.y += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // ランダムに震える
    }
}
