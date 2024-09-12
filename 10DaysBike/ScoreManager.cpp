#include "ScoreManager.h"
#include "Vec2.h"

void ScoreManager::Init()
{
	totalScore_ = std::make_unique<Score>();
	totalScore_->Init(Vec2(500,500));
	Score::Load();
}

void ScoreManager::Update()
{
	totalScore_->Update();
}

void ScoreManager::Draw()
{
	totalScore_->Draw();
	//�����L���O�̕\��
}

void ScoreManager::RegistScore(std::vector<std::string>& deadEnemyNames)
{
    bool scoreAdded = false;

	for (std::string& deadEnemyName : deadEnemyNames)
	{
        for (std::string& deadEnemyName : deadEnemyNames)
        {
            if (deadEnemyName == "BadEnemy")
            {
                totalScore_->AddScore(100);
                scoreAdded = true;
            }
            else if (deadEnemyName == "BeamEnemy")
            {
                totalScore_->AddScore(500);
                scoreAdded = true;
            }
            else if (deadEnemyName == "BulletFlyEnemy")
            {
                totalScore_->AddScore(1000);
                scoreAdded = true;
            }
            else if (deadEnemyName == "WanderEnemy")
            {
                totalScore_->AddScore(200);
                scoreAdded = true;
            }
        }

        if (scoreAdded)
        {
            totalScore_->SetIsDrum(true);
        }
	}

    if (scoreAdded)
    {
        // �V�����X�R�A�ɍ��킹�ĖڕW�X�R�A��ݒ�
        totalScore_->SetTargetScore(totalScore_->GetScore());

        // �h�������[�����J�n
        totalScore_->SetIsDrum(true);
        totalScore_->SetDrumTimer(0.0f);  // �h�������[���̃^�C�}�[�����Z�b�g
    }

	// deadEnemyNames����ɂ���
	deadEnemyNames.clear();
}

void ScoreManager::UpdateRanking()
{

}
