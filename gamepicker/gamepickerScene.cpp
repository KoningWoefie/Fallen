#include "gamepickerScene.h"
#include "defaultObject.h"
#include "src/uielement.h"
#include <src/image.h>

GamePickerScene::GamePickerScene()
{
}

GamePickerScene::~GamePickerScene()
{
}

void GamePickerScene::Update(float deltaTime)
{
}

void GamePickerScene::OnButtonClicked()
{
    std::cout << "Button Clicked!" << std::endl;
}

void GamePickerScene::OnButtonHovered()
{
    std::cout << "Button Hovered!" << std::endl;
}

void GamePickerScene::OnButtonReleased()
{
    std::cout << "Button Released!" << std::endl;
}
