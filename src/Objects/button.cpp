#include <src/Objects/button.h>

Button::Button()
{
    this->AddComponent(new Components::Image());
    this->AddComponent(new Components::Button());
    this->AddComponent(new Components::Text());
}

Button::Button(int width, int height)
{
    this->AddComponent(new Components::Image());
    this->AddComponent(new Components::Button(width, height));
    this->AddComponent(new Components::Text());
}

Button::Button(int width, int heigth, std::string text)
{
    this->AddComponent(new Components::Image());

    this->AddComponent(new Components::Button(width, heigth));

    Components::Text* textComponent = new Components::Text();
    textComponent->text = text;
    this->AddComponent(textComponent);
    textComponent = nullptr;
}

Button::Button(std::string imagePath, int width, int height, std::string text)
{
    Components::Image* imageComponent = new Components::Image();
    imageComponent->AddSprite(new Sprite(imagePath));
    this->AddComponent(imageComponent);

    this->AddComponent(new Components::Button(width, height));

    Components::Text* textComponent = new Components::Text();
    textComponent->text = text;
    this->AddComponent(textComponent);
    textComponent = nullptr;
}

Button::Button(std::string imagePath, int width, int height)
{
    Components::Image* imageComponent = new Components::Image();
    imageComponent->AddSprite(new Sprite(imagePath));
    this->AddComponent(imageComponent);

    this->AddComponent(new Components::Button(width, height));

    this->AddComponent(new Components::Text());
}

Button::Button(std::string imagePath, std::string text)
{
    Components::Image* imageComponent = new Components::Image();
    imageComponent->AddSprite(new Sprite(imagePath));
    this->AddComponent(imageComponent);

    this->AddComponent(new Components::Button());

    Components::Text* textComponent = new Components::Text();
    textComponent->text = text;
    this->AddComponent(textComponent);

    imageComponent = nullptr;
    textComponent = nullptr;
}

Button::Button(std::string imagePath)
{
    Components::Image* imageComponent = new Components::Image();
    imageComponent->AddSprite(new Sprite(imagePath));
    this->AddComponent(imageComponent);

    this->AddComponent(new Components::Button());

    this->AddComponent(new Components::Text());

    imageComponent = nullptr;
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{

}
