#pragma once
#include "AbstractSceneFactory.h"

/// <summary>
/// �Q�[���p�̃V�[���H��
/// </summary>
class SceneFactory : public AbstractSceneFactory
{
public:
	/// <summary>
	/// �V�[������
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	/// <returns>���������V�[��</returns>
	std::unique_ptr<BaseScene> CreateScene(const std::string& sceneName) override;
};



