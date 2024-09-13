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
        radius += 3;     // ”¼Œa‚ðŠg‘å
        alpha -= 5;      // ™X‚É“§–¾‚É
        if (radius > maxRadius || alpha <= 0) {
            active = false;  // ˆê’è‚Ì‘å‚«‚³‚É’B‚µ‚½‚çÁ‚¦‚é
        }
    }
}

void ExplosionCircle::Draw()
{
    if (active) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);  // “§–¾“x‚ðÝ’è
        DrawCircle(pos_.x, pos_.y, radius, GetColor(255, 100, 0), TRUE);  // ‰~‚ð•`‰æ
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);    // ƒuƒŒƒ“ƒhƒ‚[ƒh‚ðŒ³‚É–ß‚·
    }
}
