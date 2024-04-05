#include "exampleScene00.h"
#include "examples/testobj.h"
#include "src/component.h"
#include "src/image.h"
#include "src/object.h"

ExampleScene00::ExampleScene00()
{
    testObj = new TestObj();

    testObj->transform->position = glm::vec3(400.0f, 300.0f, 0.0f);
    testObj->AddComponent(new Image());

    Sprite* sprite = new Sprite("assets/RunButton.tga");
    Image* i = testObj->GetComponent<Image>();
    i->AddSprite(sprite);
    i = nullptr;

    AddChild(testObj);
}

ExampleScene00::~ExampleScene00()
{
}

void ExampleScene00::Update(float deltaTime)
{
}
