#include "KeyboardInput.h"

void KeyboardInput::Update()
{
	for (int i = 0; i < KEY_ARRAY_SIZE; i++)
	{
		oldKey_[i] = key_[i];
	}

	DxLib::GetHitKeyStateAll(key_);
}

bool KeyboardInput::GetHitKey(int key)
{
	return (key_[key]);
}

bool KeyboardInput::GetTriggerKey(int key)
{
	return (key_[key] && !oldKey_[key]);
}

bool KeyboardInput::GetTriggerReleaseKey(int key)
{
	return  (!key_[key] && oldKey_[key]);;
}

Vec2 KeyboardInput::GetSideVerticalKey()
{
	const Vec2 VEC = {

		(float)(
			KeyboardInput::GetInstance().GetHitKey(KEY_INPUT_RIGHT) ||
			KeyboardInput::GetInstance().GetHitKey(KEY_INPUT_D)
		)
		-
		(float)(
			KeyboardInput::GetInstance().GetHitKey(KEY_INPUT_LEFT) ||
			KeyboardInput::GetInstance().GetHitKey(KEY_INPUT_A)
		)
		,
		(float)(
			KeyboardInput::GetInstance().GetHitKey(KEY_INPUT_DOWN) ||
			KeyboardInput::GetInstance().GetHitKey(KEY_INPUT_S)
		)
		-
		(float)(
			KeyboardInput::GetInstance().GetHitKey(KEY_INPUT_UP) ||
			KeyboardInput::GetInstance().GetHitKey(KEY_INPUT_W)
		)
	};

	return Vec2(VEC);
}

bool KeyboardInput::GetTriggerSideKey()
{
	return GetTriggerKey(KEY_INPUT_RIGHT) || GetTriggerKey(KEY_INPUT_D)
		|| GetTriggerKey(KEY_INPUT_LEFT) || GetTriggerKey(KEY_INPUT_A);
}

bool KeyboardInput::GetHitSideKey()
{
	return GetHitRightKey()
		|| GetHitLeftKey();
}

bool KeyboardInput::GetHitRightKey()
{
	return GetHitKey(KEY_INPUT_RIGHT) || GetHitKey(KEY_INPUT_D);
}

bool KeyboardInput::GetHitLeftKey()
{
	return  GetHitKey(KEY_INPUT_LEFT) || GetHitKey(KEY_INPUT_A);
}

bool KeyboardInput::GetTriggerUpKey()
{
	return GetTriggerKey(KEY_INPUT_UP) || GetTriggerKey(KEY_INPUT_W);
}

bool KeyboardInput::GetTriggerDownKey()
{
	return GetTriggerKey(KEY_INPUT_DOWN) || GetTriggerKey(KEY_INPUT_S);
}
