#include "Score.h"

void Score::Init()
{
	scoreNum_ = 0;
}

void Score::Update(int enemyDeadNum)
{
	scoreNum_ = enemyDeadNum;
}

void Score::Draw()
{
	unsigned int color;
	//color = GetColor(255, 255, 255);
	//DrawFormatString(0, 0, color, "ÉXÉRÉA %d",scoreNum_);
}

void Score::AddScore()
{
	scoreNum_++;
}
