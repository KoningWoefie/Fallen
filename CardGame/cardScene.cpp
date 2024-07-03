#include "CardGame/cardScene.h"
#include "src/Core/config.h"

CardScene::CardScene()
{
    // Config::SetScreenMode(ScreenMode::Fullscreen);
    Config::SetTitle("Card Game");

    m_card = new Card();
    this->AddChild(m_card);
}

CardScene::~CardScene()
{
    //dtor
}

void CardScene::Update(float deltaTime)
{
    //copy ctor
}
