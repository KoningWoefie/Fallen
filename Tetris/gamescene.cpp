#include "Tetris/gamescene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::Update(float deltaTime)
{
}

void GameScene::Initialize()
{
    Config::ScreenWidth = 320;
    Config::ScreenHeight = 240;
    Config::SetScreenMode(ScreenMode::Windowed);

    Config::SetBackgroundColor(glm::vec3(0,0,0));

    _canvas = new EmptyObject();

    Components::Canvas* canvas = new Components::Canvas(glm::vec2(320, 240));
    _canvas->AddComponent(canvas);
    canvas = nullptr;

    _backgroundImage = new EmptyObject();
    Components::Image* image = new Components::Image();
    image->AddSprite(new Sprite("assets/MainSceneBackground.tga"));
    _backgroundImage->AddComponent(image);

    _canvas->AddChild(_backgroundImage);
    this->AddChild(_canvas);

    colNum = 10;
    rowNum = 20;

    CreateGrid();
}

void GameScene::CreateGrid()
{
    _gridObject = new EmptyObject();
    Components::UIElement* uiElement = new Components::UIElement();
    uiElement->SetAlignment(Components::UIAlignment::Top);
    _gridObject->AddComponent(uiElement);
    _gridObject->transform->position = glm::vec3(-36.0f, 44.0f, 0.0f);
    _canvas->AddChild(_gridObject);

    for(int x = 0; x < colNum; x++)
    {
        _grid.push_back(std::vector<EmptyObject*>());
        for(int y = 0; y < rowNum; y++)
        {
            _grid[x].push_back(new EmptyObject());
            Components::Image* image = new Components::Image();
            image->AddSprite(new Sprite("assets/EmptyBlock.tga", 0));
            _grid[x][y]->AddComponent(image);
            _grid[x][y]->transform->scale = glm::vec3(0.25f, 0.25f, 1.0f);
            _gridObject->AddChild(_grid[x][y]);
            _grid[x][y]->transform->position = glm::vec3(8.0f * x, 8.0f * y, 0.0f);
        }
    }
}
