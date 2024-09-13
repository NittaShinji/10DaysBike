#pragma once
#include "DxLib.h"
#include <cstdlib> 
#include "Vec2.h"

class ExplosionCircle
{
public:
    void Init(Vec2 pos,int randNum);
    void Update(Vec2 pos);
    void Draw();

    // 円が終了しているか確認
    bool IsFinished() {
        return !active;
    }

    void SetInfo(Vec2 pos, int maxR) 
    {
        pos_ = pos;
        maxRadius = maxR;
    };

    //ExplosionCircle(int startX, int startY, int maxR) {}
    
private:

    //爆発の位置
    Vec2 pos_;
    //半径
    float radius;
    //透明度
    int alpha;
    //爆発が有効かどうか
    bool active;
    //最大半径
    int maxRadius;   
};

