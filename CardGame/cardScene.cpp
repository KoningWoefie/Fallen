#include "CardGame/cardScene.h"
#include "src/Core/config.h"

CardScene::CardScene()
{
    // Config::SetScreenMode(ScreenMode::Fullscreen);
    Config::SetTitle("Card Game");
    Config::SetBackgroundColor(glm::vec3(54, 89, 74));

    _card = new Card(2, CardType::CLUBS);
    _inputField = new Presets::InputField();
    _inputField->transform->position = glm::vec3(Config::ScreenWidth/2, 500, 0);

    _titleText = new Presets::EmptyObject();

    _titleText->AddComponent(new Text((char *)"fonts/HeadlinerNo.45.ttf", 128));
    _titleText->GetComponent<Text>()->text = "Card Game";
    _titleText->GetComponent<Text>()->centered = true;

    _titleText->transform->position = glm::vec3(Config::ScreenWidth/2, 0, 0);

    this->AddChild(_titleText);

    // this->AddChild(_card);
    this->AddChild(_inputField);
    _inputField->GetComponent<Text>()->centered = true;
    new Deck();
}

CardScene::~CardScene()
{
    //dtor
}

void CardScene::Update(float deltaTime)
{
}
