#include <src/Presets/button.h>

namespace Presets
{
    Button::Button()
    {
        this->AddComponent(new FallenUI::Image());
        this->AddComponent(new FallenUI::Button());
        this->AddComponent(new Text());
    }

    Button::Button(int width, int height)
    {
        this->AddComponent(new FallenUI::Image());
        this->AddComponent(new FallenUI::Button(width, height));
        this->AddComponent(new Text());
    }

    Button::Button(int width, int heigth, std::string text)
    {
        this->AddComponent(new FallenUI::Image());

        this->AddComponent(new FallenUI::Button(width, heigth));

        Text* textComponent = new Text();
        textComponent->text = text;
        this->AddComponent(textComponent);
        textComponent = nullptr;
    }

    Button::Button(std::string imagePath, int width, int height, std::string text)
    {
        FallenUI::Image* imageComponent = new FallenUI::Image();
        imageComponent->AddSprite(new Sprite(imagePath));
        this->AddComponent(imageComponent);

        this->AddComponent(new FallenUI::Button(width, height));

        Text* textComponent = new Text();
        textComponent->text = text;
        this->AddComponent(textComponent);
        textComponent = nullptr;
    }

    Button::Button(std::string imagePath, int width, int height)
    {
        FallenUI::Image* imageComponent = new FallenUI::Image();
        imageComponent->AddSprite(new Sprite(imagePath));
        this->AddComponent(imageComponent);

        this->AddComponent(new FallenUI::Button(width, height));

        this->AddComponent(new Text());
    }

    Button::Button(std::string imagePath, std::string text)
    {
        FallenUI::Image* imageComponent = new FallenUI::Image();
        imageComponent->AddSprite(new Sprite(imagePath));
        this->AddComponent(imageComponent);

        this->AddComponent(new FallenUI::Button());

        Text* textComponent = new Text();
        textComponent->text = text;
        this->AddComponent(textComponent);

        imageComponent = nullptr;
        textComponent = nullptr;
    }

    Button::Button(std::string imagePath)
    {
        FallenUI::Image* imageComponent = new FallenUI::Image();
        imageComponent->AddSprite(new Sprite(imagePath));
        this->AddComponent(imageComponent);

        this->AddComponent(new FallenUI::Button());

        this->AddComponent(new Text());

        imageComponent = nullptr;
    }

    Button::~Button()
    {
    }

    void Button::Update(float deltaTime)
    {

    }
}
