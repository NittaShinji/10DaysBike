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

    // �~���I�����Ă��邩�m�F
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

    //�����̈ʒu
    Vec2 pos_;
    //���a
    float radius;
    //�����x
    int alpha;
    //�������L�����ǂ���
    bool active;
    //�ő唼�a
    int maxRadius;   
};

