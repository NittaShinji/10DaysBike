#pragma once
#include "Vec2.h"

//‘O•ûéŒ¾
class Player;

class BackGround
{
public:
	static const int backGroundGraphNum = 3;
	static const int kBackGroundGraphWidth = 640;
	static const int kBackGroundGraphHeight = 940;

public:
	struct BackGroundObj
	{
		Vec2 pos;
		Vec2 defaultPos;
		int graphHandle;
	};

private:

	BackGroundObj backGroundObj[backGroundGraphNum];
	int scrollValue_;

public:

	void Init();
	void Update(int playerSpeed);
	void Draw();
};

