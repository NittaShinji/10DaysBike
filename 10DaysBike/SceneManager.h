#pragma once
#include "BaseScene.h"
#include "AbstractSceneFactory.h"

class SceneManager final
{
public: //�����o�֐�

	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	/// <returns>�V���O���g���C���X�^���X</returns>
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	/// <summary>
	/// �V�[���\��
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	void ChangeScene(const std::string& sceneName);

	//�V�[���t�@�N�g���[�̃Z�b�^�[
	void SetSceneFactory(std::unique_ptr<AbstractSceneFactory> sceneFactory) { sceneFactory_ = std::move(sceneFactory); }

private:

	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//�R�s�[�R���X�g���N�^�̖���
	SceneManager(const SceneManager& sceneManager) = delete;
	//������Z�q�̖���
	SceneManager& operator=(const SceneManager& sceneManager) = delete;

	//�V�[���t�@�N�g���[
	std::unique_ptr<AbstractSceneFactory> sceneFactory_ = nullptr;
	//���̃V�[��
	std::unique_ptr<BaseScene> nextScene_ = nullptr;
	//���̃V�[��(���s���V�[��)
	std::unique_ptr<BaseScene> scene_ = nullptr;
};

