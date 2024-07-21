#include "CardGame/homescene.h"
#include "src/Presets/canvas.h"
#include "src/Presets/emptyobject.h"

HomeScene::HomeScene()
{
    Config::SetBackgroundColor(glm::vec3(54, 89, 74));
    Config::ScreenWidth = 1800;
    Config::ScreenHeight = 1169;
    Config::SetScreenMode(ScreenMode::Windowed);
    _canvas = new Presets::Canvas(glm::vec2(1800, 1080));

    _titleImage = new Presets::EmptyObject();
    FallenUI::Image* image = new FallenUI::Image();
    image->AddSprite(new Sprite("assets/Logo_CardGame.tga"));
    _titleImage->AddComponent(image);
    image->pivot = glm::vec2(0.5f, 0.5f);
    image = nullptr;

    _text = new Presets::EmptyObject();
    Text* text = new Text((char *)"fonts/Times New Roman.ttf");
    text->text = "Press any key to start";
    text->centered = true;
    _text->AddComponent(text);
    _text->transform->position = glm::vec3(0, 400, 0);
    text = nullptr;

    _startButton = new Presets::EmptyObject();
    FallenUI::Button* button = new FallenUI::Button(Config::ScreenWidth, Config::ScreenHeight);
    button->SetOnPress(std::bind(&HomeScene::StartGame, this));
    _startButton->AddComponent(button);
    button = nullptr;

    _canvas->AddChild(_titleImage);
    _canvas->AddChild(_text);
    _canvas->AddChild(_startButton);
    this->AddChild(_canvas);
}

HomeScene::~HomeScene()
{
    delete _canvas;
    delete _titleImage;
}

void HomeScene::Update(float deltaTime)
{
    if(Input()->AnyKeyDown())
    {
        _startButton->GetComponent<FallenUI::Button>()->Press();
    }
}

void HomeScene::StartGame()
{
    std::cout << "Start Game" << std::endl;
}
