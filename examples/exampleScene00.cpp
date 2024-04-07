#include "exampleScene00.h"
#include <src/image.h>

ExampleScene00::ExampleScene00()
{
    testObj = new TestObj();

    testObj->transform->position = glm::vec3(400.0f, 300.0f, 0.0f);
    testObj->AddComponent(new Image());

    SlicedSprite* sprite = new SlicedSprite("assets/buttons-down.tga", 25, 25, 25, 25);
    Image* i = testObj->GetComponent<Image>();
    i->AddSprite(sprite);
    i = nullptr;

    testObj->AddComponent(new Text());
    Text* t = testObj->GetComponent<Text>();
    t->text = "Heppo World!";

    AddChild(testObj);
}

ExampleScene00::~ExampleScene00()
{
}

void ExampleScene00::Update(float deltaTime)
{
}
