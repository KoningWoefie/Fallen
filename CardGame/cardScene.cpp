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

    this->AddChild(_card);
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
