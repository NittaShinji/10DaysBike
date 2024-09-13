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
        radius += 3;     // ���a���g��
        alpha -= 5;      // ���X�ɓ�����
        if (radius > maxRadius || alpha <= 0) {
            active = false;  // ���̑傫���ɒB�����������
        }
    }
}

void ExplosionCircle::Draw()
{
    if (active) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);  // �����x��ݒ�
        DrawCircle(pos_.x, pos_.y, radius, GetColor(255, 100, 0), TRUE);  // �~��`��
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);    // �u�����h���[�h�����ɖ߂�
    }
}
