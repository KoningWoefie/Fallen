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
}
