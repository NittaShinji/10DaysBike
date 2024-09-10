#pragma once
#include<DxLib.h>
#include<memory>
#include"Vec2.h"

class KeyboardInput
{
private:
	static const uint16_t KEY_ARRAY_SIZE = 256;
private:
	char key_[KEY_ARRAY_SIZE];
	char oldKey_[KEY_ARRAY_SIZE];

public:
	KeyboardInput() { ; }
	~KeyboardInput() { ; }
public:
	//コピーコンストラクタを無効
	KeyboardInput(const KeyboardInput& obj) = delete;
	//代入演算子も
	KeyboardInput& operator=(const KeyboardInput& obj) = delete;

	static KeyboardInput& GetInstance() { static KeyboardInput ins; return ins; }
public:
	void Update();
public:
	bool GetHitKey(int key);
	bool GetTriggerKey(int key);
	bool GetTriggerReleaseKey(int key);
public:
	Vec2 GetSideVerticalKey();
	bool GetTriggerSideKey();
	bool GetHitSideKey();
	bool GetHitRightKey();
	bool GetHitLeftKey();
};

