#include "SceneFactory.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "ResultScene.h"

std::unique_ptr<BaseScene> SceneFactory::CreateScene(const std::string& sceneName)
{
    //���̃V�[���𐶐�
    std::unique_ptr<BaseScene> newScene = nullptr;

    if (sceneName == "TITLE")
    {
        newScene = std::make_unique<TitleScene>();
    }
    else if (sceneName == "GAME")
    {
        newScene = std::make_unique<GameScene>();
    }
    else if (sceneName == "CLEAR")
    {
        newScene = std::make_unique<ClearScene>();
    }
    else if (sceneName == "RESULT")
    {
        newScene = std::make_unique<ResultScene>();
    }

    return newScene;
}
