#include "ExplosionCircle.h"

void ExplosionCircle::Init(Vec2 pos,int randNum)
{
    pos_ = pos;
    radius = 0;
    alpha = 255;
    active = true;
    maxRadius = randNum;
}

void ExplosionCircle::Update(Vec2 pos)
{
    if (active) {
        pos_ = pos;
        radius += 3;     // 半径を拡大
        alpha -= 5;      // 徐々に透明に
        if (radius > maxRadius || alpha <= 0) {
            active = false;  // 一定の大きさに達したら消える
        }
    }
}

void ExplosionCircle::Draw()
{
    if (active) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);  // 透明度を設定
        DrawCircle(pos_.x, pos_.y, radius, GetColor(255, 100, 0), TRUE);  // 円を描画
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);    // ブレンドモードを元に戻す
    }
}
