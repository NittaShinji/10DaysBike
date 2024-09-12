#include "GameState.h"

void GameState::Init()
{
	scoreManager_ = std::make_unique<ScoreManager>();
	scoreManager_->Init();
	isClear_ = false;
}

void GameState::Update()
{
	scoreManager_->Update();
}

void GameState::Draw()
{
	scoreManager_->Draw();
}
