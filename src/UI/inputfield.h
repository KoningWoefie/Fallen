#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include <src/Core/component.h>
#include <src/Core/inputmanager.h>

namespace Components
{
    class InputField : public Component
    {
    public:
        InputField();
        virtual ~InputField();

        void RegisterInput();
        void ToggleRegisterInput();
        bool ShouldRegisterInput() { return _shouldRegisterInput; };
        std::string GetInput() { return _input; };
    private:
        std::string _input;
        bool _shouldRegisterInput;
    };
}

#endif
