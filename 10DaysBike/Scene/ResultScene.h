#pragma once
#include "BaseScene.h"

class ResultScene : public BaseScene
{
public:

	//静的初期化
	static void StaticInitialize();

	//リソース削除
	static void DeleteResource();

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
	//登録中画像
	static int registHandle_;

	//ゲーム内BGM
	static int gameOverSoundHandle_;
	//スタート音
	static int clearSoundHandle_;

	const int waitScoreTime = 60;
	int waitScoreTimer_ = waitScoreTime;

	bool isStartDrumScore_ = false;
};