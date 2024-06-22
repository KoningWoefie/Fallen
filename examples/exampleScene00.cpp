#include "exampleScene00.h"
#include "examples/testobj.h"
#include "src/Presets/button.h"
#include "src/UI/uielement.h"
#include <src/UI/image.h>

ExampleScene00::ExampleScene00()
{
    canvas = new TestObj();
    FallenUI::Canvas* c = new FallenUI::Canvas(glm::vec2(1280, 720));
    canvas->AddComponent(c);
    canvas->transform->position = glm::vec3(c->GetCanvasWidth()/2, c->GetCanvasHeight()/2, 0.0f);
    button = new Presets::Button("assets/RunButton.tga");

    button->transform->position = glm::vec3(0.0f, 0.0f, 0.0f);

    FallenUI::Button* b = button->GetComponent<FallenUI::Button>();
    b->SetOnHover(std::bind(&ExampleScene00::OnButtonHovered, this));
    b->SetOnPress(std::bind(&ExampleScene00::OnButtonClicked, this));
    b->SetOnRelease(std::bind(&ExampleScene00::OnButtonReleased, this));

    // AnimatedSprite* sprite = new AnimatedSprite("assets/Sprite_Sheet_G4.tga", 4, 4, 0.5f);
    // FallenUI::Image* i = button->GetComponent<FallenUI::Image>();
    // i->AddSprite(sprite);
    // sprite->AddAnimation({1,2,3,4});
    // i = nullptr;

    button->AddComponent(new Text());
    Text* t = button->GetComponent<Text>();
    t->text = "Heppo World!";

    AddChild(canvas);
    canvas->AddChild(button);
}

ExampleScene00::~ExampleScene00()
{
}

void ExampleScene00::Update(float deltaTime)
{
    if(Input()->GetKey(KeyCode::D))
    {
        button->transform->position.x += 10.0f * deltaTime;
        // dynamic_cast<SpriteSheet*>(button->GetComponent<FallenUI::Image>()->GetSprite())->SetCurrentFrame(2);
    }
}

void ExampleScene00::OnButtonClicked()
{
    std::cout << "Button Clicked!" << "\n";
}

void ExampleScene00::OnButtonHovered()
{
    std::cout << "Button Hovered!" << "\n";
}

void ExampleScene00::OnButtonReleased()
{
    std::cout << "Button Released!" << "\n";
}
