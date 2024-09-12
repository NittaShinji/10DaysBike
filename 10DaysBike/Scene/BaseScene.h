#pragma once

//�O���錾
class SceneManager;
class GameState;

/// <summary>
/// �V�[�����N���X
/// </summary>
class BaseScene
{
public:

	//������
	virtual void Initialize() {};

	//���t���[���X�V
	virtual void Update() {};

	//�I��
	virtual void Finalize() {};

	//�`��
	virtual void Draw() {};

public: //�����o�֐�

	virtual ~BaseScene() = default;
	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }

public:

	void SetGameState(GameState* gameState)
	{
		gameState_ = gameState;
	}

public: 

protected:

	//�V�[���}�l�[�W��
	SceneManager* sceneManager_ = nullptr;
	//�V�[���Ԃŋ��L���s���Q�[�����
	GameState* gameState_ = nullptr;
};


