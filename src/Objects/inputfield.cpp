#include "src/UI/button.h"
#include "src/UI/inputfield.h"
#include <src/Objects/inputfield.h>

InputField::InputField() : Object()
{
    _text = new Components::Text();
    _text->text = "";

    Components::Image* i = new Components::Image();
    i->AddSprite(new SlicedSprite("Assets/buttons-down.tga", 20,20,20,20));

    _inputField = new Components::InputField();

    Components::Button* b = new Components::Button();

    b->SetOnPress(std::bind(&Components::InputField::ToggleRegisterInput, _inputField));

    AddComponent(i);
    AddComponent(_inputField);
    AddComponent(b);
    AddComponent(_text);

    i = nullptr;
    b = nullptr;
}

InputField::~InputField()
{
    delete _text;
}

void InputField::Update(float deltaTime)
{
    if(!_inputField->GetInput().empty() && _inputField->ShouldRegisterInput()) _text->text = _inputField->GetInput();
    else if(_inputField->GetInput().empty()) _text->text = "";
}
