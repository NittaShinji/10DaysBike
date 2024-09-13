#include "ExplosionStaging.h"
#include "DxLib.h"

void ExplosionStaging::Init(Vec2 pos,int numCircles)
{
    //circles.clear();  // �����̉~���N���A
    //for (int i = 0; i < numCircles; ++i) {
    //    int randomX = pos.x + (rand() % 41 - 20); // ���S�ʒu����}20�͈̔͂Ń����_���Ȉʒu
    //    int randomY = pos.y + (rand() % 41 - 20);
    //    int maxR = rand() % 50 + 30;  // �����_���ȍő唼�a (30 - 80)
    //    circles.emplace_back(Vec2(randomX,randomY), maxR);  // �V�����~��ǉ�
    //}

    int randomX = pos.x + (rand() % 41 - 20); // ���S�ʒu����}20�͈̔͂Ń����_���Ȉʒu
    int randomY = pos.y + (rand() % 41 - 20);
    int maxR = rand() % 50 + 30;  // �����_���ȍő唼�a (30 - 80)

    //�e�𐶐����A������
    std::unique_ptr<ExplosionCircle> newCircle = std::make_unique<ExplosionCircle>();
    newCircle->Init(Vec2(randomX,randomY), maxR);

    //�e��e�}�l�[�W���[�ɓo�^����
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
            active = false;  // �S�Ẳ~���I�������甚�����I��
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

    //DrawCircle(pos_.x, pos_.y, radius, GetColor(255, 100, 0), TRUE);  // �~��`��
}

void ExplosionStaging::Shake(Vec2& enemyPos)
{
    if (active) {
        //enemyPos.x += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // �����_���ɐk����
        //enemyPos.y += (rand() % (shakeRange * 2 + 1)) - shakeRange;  // �����_���ɐk����
    }
}
