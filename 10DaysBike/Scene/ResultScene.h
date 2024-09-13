#pragma once
#include "BaseScene.h"

class ResultScene : public BaseScene
{
public:

	//静的初期化
	static void StaticInitialize();

	//初期化
	void Initialize() override;

	//毎フレーム更新
	void Update() override;

	//描画
	void Draw() override;

private:

	//クリア画像
	static int clearImageHandle_;
	//ゲームオーバー画像
	static int gameOverImageHandle_;
};