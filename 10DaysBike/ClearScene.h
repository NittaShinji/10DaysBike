#pragma once
#include "BaseScene.h"

class ClearScene : public BaseScene
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

private:

	//�N���A�X�v���C�g

};

