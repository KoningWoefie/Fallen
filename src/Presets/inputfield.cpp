#include "src/UI/button.h"
#include "src/UI/inputfield.h"
#include <src/Presets/inputfield.h>

namespace Presets
{
    InputField::InputField() : Object()
    {
        _text = new Text();
        _text->text = "";

        FallenUI::Image* i = new FallenUI::Image();
        i->AddSprite(new SlicedSprite("Assets/buttons-down.tga", 20,20,20,20));

        _inputField = new FallenUI::InputField();

        FallenUI::Button* b = new FallenUI::Button();

        b->SetOnPress(std::bind(&FallenUI::InputField::ToggleRegisterInput, _inputField));

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
}
