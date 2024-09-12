#pragma once

//前方宣言
class SceneManager;

/// <summary>
/// シーン基底クラス
/// </summary>
class BaseScene
{
public:

	//初期化
	virtual void Initialize() {};

	//毎フレーム更新
	virtual void Update() {};

	//終了
	virtual void Finalize() {};

	//描画
	virtual void Draw() {};

public: //メンバ関数

	virtual ~BaseScene() = default;
	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }

protected:

	//シーンマネージャ
	SceneManager* sceneManager_ = nullptr;
};


