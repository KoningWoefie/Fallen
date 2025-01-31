#include "CardGame/cardScene.h"
#include "src/Core/component.h"
#include "src/Core/config.h"

CardScene::CardScene()
{
}

void CardScene::Initialize()
{
    Config::SetTitle("Card Game");
    Config::SetBackgroundColor(glm::vec3(54, 89, 74));

    _inputField = new InputField();
    _inputField->transform->position = glm::vec3(Config::ScreenWidth/2, 500, 0);

    _titleText = new EmptyObject();

    _titleText->AddComponent(new Components::Text((char *)"fonts/Times New Roman.ttf", 128));
    _titleText->GetComponent<Components::Text>()->text = "Card Game";
    _titleText->GetComponent<Components::Text>()->centered = true;

    _titleText->transform->position = glm::vec3(Config::ScreenWidth/2, 0, 0);

    this->AddChild(_titleText);

    this->AddChild(_inputField);
    _inputField->GetComponent<Components::Text>()->centered = true;
    Deck* deck = new Deck();
    _hand = new Hand();
    for(int i = 0; i < 7; i++)
    {
        _hand->AddCard(deck->Draw());
        this->AddChild(_hand->GetCard(i));
    }
    _hand->SortHand(0);
    for(int i = 0; i < 7; i++)
    {
        _hand->GetCard(i)->transform->position = glm::vec3(100 + i * 100, 200, 0);
    }
}

CardScene::~CardScene()
{
    //dtor
}

void CardScene::Update(float deltaTime)
{
}
