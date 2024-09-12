#pragma once
#include "Vec2.h"

//ëOï˚êÈåæ
class Player;
class IPlayerState;

class BackGround
{
public:
	static const int backGroundGraphNum = 3;
	static const int kBackGroundGraphWidth = 640;
	static const int kBackGroundGraphHeight = 940;
	static const int kBackGroundScllolNum = 4.0f;

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
	void Update(int playerSpeed, IPlayerState* playerState);
	void Draw();
};

