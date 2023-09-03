#include "exampleScene00.h"

ExampleScene00::ExampleScene00()
{
    // _texturePath = "assets/RunButton.tga";
    _width = 200;
    _height = 200;

    // _radius = 1;

    position = glm::vec3(200.0f, 300.0f, 0.0f);

    color = glm::vec4(0,0,255,255);

    st = new SheetTest("assets/Sprite_Sheet_G4.tga", 4, 4, 1.0f);

    _pivot = glm::vec2(0.0f,0.0f);
    
    this->AddChild(st);
    st->position = glm::vec3(400.0f, 0.0f, 0.0f);

    _text = new Text("fonts/ponde___.ttf", 32);
    _text->Message("Heppo World!");
    _text->pivot = glm::vec2(0.5f, 0.5f);
}

ExampleScene00::~ExampleScene00()
{
}

void ExampleScene00::update(float deltaTime)
{
    if(Input()->getKey(KeyCode::Right))
    {
        position.x += 100.0f * deltaTime;
    }
}