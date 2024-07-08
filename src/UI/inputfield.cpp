#include "src/Core/inputmanager.h"
#include <src/UI/inputfield.h>

namespace FallenUI
{
    InputField::InputField() : Component()
    {
        _input = "";
        _shouldRegisterInput = false;
    }

    InputField::~InputField()
    {
        _input = "";
    }

    void InputField::RegisterInput()
    {
        if (InputManager::input()->GetKey(KeyCode::Backspace))
        {
            if (_input.length() > 0)
            {
                _input.pop_back();
            }
            return;
        }
        for (int i = 32; i < 96; i++)
        {
            char pi = InputManager::input()->GetChar((KeyCode)i);
            if (pi != 0)
            {
                _input += pi;
            }
        }

        for (unsigned int i = 256; i < GLFW_KEY_LAST; i++)
        {
            char pi = InputManager::input()->GetChar((KeyCode)i);
            if (pi != 0)
            {
                _input += pi;
            }
        }

    }

    void InputField::ToggleRegisterInput()
    {
        _shouldRegisterInput = !_shouldRegisterInput;
    }
}
