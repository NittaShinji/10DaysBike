#pragma once
#include "BaseScene.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public BaseScene
{
public:

	~TitleScene();

	//静的初期化
	static void StaticInitialize();

	//初期化
	void Initialize() override;

	//毎フレーム更新
	void Update() override;

	//描画
	void Draw() override;

private:

	//スプライト
	static int titleHandle_;
};



