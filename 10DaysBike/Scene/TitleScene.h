#pragma once
#include "BaseScene.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public BaseScene
{
public:

	//�ÓI������
	static void StaticInitialize();

	//������
	void Initialize() override;

	//���t���[���X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���\�[�X�폜
	static void DeleteResource();

private:

	//�X�v���C�g
	static int titleHandle_;

	//�Q�[����BGM
	static int bgmHandle_;

	//BGM�^�C�}�[
	const int kDefaultPlaytoTime_ = 20;
	int playTimer_ = 0;

	//�炵�����ǂ���
	bool isPlayBgm_ = false;
};



