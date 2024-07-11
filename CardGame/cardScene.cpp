#include "CardGame/cardScene.h"
#include "src/Core/config.h"

CardScene::CardScene()
{
    // Config::SetScreenMode(ScreenMode::Fullscreen);
    Config::SetTitle("Card Game");
    Config::SetBackgroundColor(glm::vec3(54, 89, 74));

    _card = new Card(2, CardType::CLUBS);
    _inputField = new Presets::InputField();
    _inputField->transform->position = glm::vec3(400, 300, 0);

    this->AddChild(_card);
    this->AddChild(_inputField);
    new Deck();
}

CardScene::~CardScene()
{
    //dtor
}

void CardScene::Update(float deltaTime)
{
}
