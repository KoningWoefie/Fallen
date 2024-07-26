#include "CardGame/homescene.h"
#include "src/Core/sprite.h"
#include "src/Objects/emptyobject.h"
#include "src/UI/uielement.h"
#include <src/Core/scenemanager.h>

HomeScene::HomeScene()
{
}

void HomeScene::Initialize()
{
    Config::SetBackgroundColor(glm::vec3(54, 89, 74));
    Config::ScreenWidth = 1800;
    Config::ScreenHeight = 1080;
    Config::SetScreenMode(ScreenMode::Windowed);
    _canvas = new EmptyObject();
    _canvas->AddComponent(new Components::Canvas(glm::vec2(1800, 1080)));

    _titleImage = new EmptyObject();
    Components::Image* image = new Components::Image();
    image->AddSprite(new Sprite("assets/Logo_CardGame.tga"));
    _titleImage->AddComponent(image);
    image->pivot = glm::vec2(0.5f, 0.5f);
    image = nullptr;

    _text = new EmptyObject();
    Components::Text* text = new Components::Text((char *)"fonts/Times New Roman.ttf");
    text->text = "Press any key to start";
    text->centered = true;
    _text->AddComponent(text);
    _text->transform->position = glm::vec3(0, 400, 0);
    text = nullptr;

    _startButton = new EmptyObject();
    Components::Button* button = new Components::Button(Config::ScreenWidth, Config::ScreenHeight);
    button->SetOnPress(std::bind(&HomeScene::StartGame, this));
    _startButton->AddComponent(button);
    button = nullptr;

    for(int i = 0; i < 10; i++)
    {
        Button* column = new Button();
        image = column->GetComponent<Components::Image>();
        image->AddSprite(new SlicedSprite("assets/square.tga", 2, 2, 2, 2));
        image->GetSprite()->SetFilter(0);
        column->transform->scale = glm::vec3(8.0f, 1.0f, 1.0f);
        column->AddComponent(new Components::UIElement());
        column->GetComponent<Components::UIElement>()->SetAlignment(Components::UIAlignment::Top);
        column->transform->position = glm::vec3(0, 200 * i, 0);
        _columns.push_back(column);
        column = nullptr;
    }


    _canvas->AddChild(_titleImage);
    _canvas->AddChild(_text);
    _canvas->AddChild(_startButton);
    for(int i = 0; i < _columns.size(); i++)
    {
        _canvas->AddChild(_columns[i]);
    }
    this->AddChild(_canvas);
}

HomeScene::~HomeScene()
{
    delete _canvas;
    delete _titleImage;
    delete _startButton;
    delete _text;
}

void HomeScene::Update(float deltaTime)
{
    if(Input()->AnyKeyDown())
    {
        _startButton->GetComponent<Components::Button>()->Press();
    }
}

void HomeScene::StartGame()
{
    SceneManager::GetInstance()->NextScene();
}
