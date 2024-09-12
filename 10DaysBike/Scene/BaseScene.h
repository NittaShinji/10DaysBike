#pragma once

//�O���錾
class SceneManager;

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

protected:

	//�V�[���}�l�[�W��
	SceneManager* sceneManager_ = nullptr;
};


