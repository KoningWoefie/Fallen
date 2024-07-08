#ifndef INPUTFIELDPRESETS_H
#define INPUTFIELDPRESETS_H

#include <src/Core/object.h>
#include <src/UI/button.h>
#include <src/UI/inputfield.h>
#include <src/UI/image.h>
#include <src/Core/text.h>
#include <src/Core/sprite.h>

namespace Presets
{
    class InputField : public Object
    {
    public:
        InputField();
        ~InputField();

        virtual void Update(float deltaTime);
    private:
        Text* _text;
        FallenUI::InputField* _inputField;
    };
}
#endif
