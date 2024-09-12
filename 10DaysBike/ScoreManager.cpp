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
	//ƒ‰ƒ“ƒLƒ“ƒO‚Ì•\¦
}

void ScoreManager::UpdateRanking()
{

}
