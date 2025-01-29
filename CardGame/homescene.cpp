#include "CardGame/homescene.h"
#include "src/Core/sprite.h"
#include "src/Objects/emptyobject.h"
#include "src/Objects/inputfield.h"
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
    button->SetOnPress(std::bind(&HomeScene::GoToChoice, this));
    _startButton->AddComponent(button);
    button = nullptr;

    _canvas->AddChild(_titleImage);
    _canvas->AddChild(_text);
    _canvas->AddChild(_startButton);
    this->AddChild(_canvas);

    _hostButton = nullptr;
    _joinButton = nullptr;
    _exitButton = nullptr;
    _hostPanel = nullptr;
}

HomeScene::~HomeScene()
{
    if(_canvas != nullptr) delete _canvas;
    if(_titleImage != nullptr) delete _titleImage;
    if(_startButton != nullptr) delete _startButton;
    if(_text != nullptr) delete _text;
    for (int i = 0; i < _columns.size(); i++)
    {
        delete _columns[i];
        _columns[i] = nullptr;
    }
    _columns.clear();
}

void HomeScene::Update(float deltaTime)
{
    if(Input()->AnyKeyDown())
    {
        _startButton->GetComponent<Components::Button>()->Press();
    }
}

void HomeScene::GoToChoice()
{
    _canvas->RemoveChild(_titleImage);
    _canvas->RemoveChild(_startButton);
    _canvas->RemoveChild(_text);

    delete _titleImage;
    delete _startButton;
    delete _text;

    _titleImage = nullptr;
    _startButton = nullptr;
    _text = nullptr;

    for(int i = 0; i < 10; i++)
    {
        Button* column = new Button();
        Components::Image* image = column->GetComponent<Components::Image>();
        image->AddSprite(new SlicedSprite("assets/square.tga", 2, 2, 2, 2));
        image->GetSprite()->SetFilter(0);
        column->transform->scale = glm::vec3(8.0f, 1.0f, 1.0f);
        column->AddComponent(new Components::UIElement());
        column->GetComponent<Components::UIElement>()->SetAlignment(Components::UIAlignment::Top);
        column->transform->position = glm::vec3(200, 136 + 200 * i, 0);
        _columns.push_back(column);
        column = nullptr;
        image = nullptr;
    }
    for(int i = 0; i < _columns.size(); i++)
    {
        _canvas->AddChild(_columns[i]);
    }

    _hostButton = new Button();
    Components::Image* image = _hostButton->GetComponent<Components::Image>();
    image->AddSprite(new SlicedSprite("assets/square.tga", 2, 2, 2, 2));
    image->GetSprite()->SetFilter(0);
    _hostButton->transform->scale = glm::vec3(3.0f, 1.0f, 1.0f);
    _hostButton->AddComponent(new Components::UIElement());
    _hostButton->GetComponent<Components::UIElement>()->SetAlignment(Components::UIAlignment::TopLeft);
    _hostButton->GetComponent<Components::Text>()->text = "Host";
    _hostButton->GetComponent<Components::Text>()->centered = true;
    _hostButton->transform->position = glm::vec3(256, 136, 0);
    _hostButton->GetComponent<Components::Button>()->SetOnPress(std::bind(&HomeScene::GoToHost, this));
    image = nullptr;
    _canvas->AddChild(_hostButton);


    _joinButton = new Button();
    image = _joinButton->GetComponent<Components::Image>();
    image->AddSprite(new SlicedSprite("assets/square.tga", 2, 2, 2, 2));
    image->GetSprite()->SetFilter(0);
    _joinButton->transform->scale = glm::vec3(3.0f, 1.0f, 1.0f);
    _joinButton->AddComponent(new Components::UIElement());
    _joinButton->GetComponent<Components::UIElement>()->SetAlignment(Components::UIAlignment::Left);
    _joinButton->GetComponent<Components::Text>()->text = "Join";
    _joinButton->GetComponent<Components::Text>()->centered = true;
    _joinButton->transform->position = glm::vec3(256, 0, 0);
    image = nullptr;
    _canvas->AddChild(_joinButton);
}

void HomeScene::GoToHost()
{
    if(_hostPanel != nullptr) return;
    for(int i = 0; i < _columns.size(); i++)
    {
        _canvas->RemoveChild(_columns[i]);
    }
    _hostPanel = new EmptyObject();
    Components::Image* image = new Components::Image();
    image->AddSprite(new SlicedSprite("assets/square.tga", 2, 2, 2, 2));
    image->GetSprite()->SetFilter(0);
    _hostPanel->AddComponent(image);
    image = nullptr;
    _hostPanel->transform->scale = glm::vec3(8.0f, 4.0f, 1.0f);
    _hostPanel->AddComponent(new Components::UIElement());
    _canvas->AddChild(_hostPanel);

    InputField* inputField = new InputField();
    image = inputField->GetComponent<Components::Image>();
    image->AddSprite(new SlicedSprite("assets/square.tga", 2, 2, 2, 2));
    image->GetSprite()->SetFilter(0);;
    inputField->AddComponent(new Components::UIElement());
    inputField->GetComponent<Components::UIElement>()->SetAlignment(Components::UIAlignment::Top);

    inputField->transform->scale = glm::vec3(0.8f, 0.8f, 1.0f);
    inputField->transform->position = glm::vec3(0, 0, 0);

    _hostPanel->AddChild(inputField);
    inputField = nullptr;
}

void HomeScene::Host()
{
}

void HomeScene::Join()
{

}
