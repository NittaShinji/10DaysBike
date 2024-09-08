#pragma once

class Score
{
public:
	void Init();
	void Update(int enemyDeadNum);
	void Draw();
	void AddScore();
private:
	int scoreNum_;

public:

	int GetScore() { return scoreNum_; }
};

