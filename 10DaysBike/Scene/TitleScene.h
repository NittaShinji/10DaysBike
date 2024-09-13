#pragma once
#include "BaseScene.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public BaseScene
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

	//リソース削除
	static void DeleteResource();

private:

	//スプライト
	static int titleHandle_;

	//ゲーム内BGM
	static int bgmHandle_;

	//BGMタイマー
	const int kDefaultPlaytoTime_ = 20;
	int playTimer_ = 0;

	//鳴らしたかどうか
	bool isPlayBgm_ = false;
};



