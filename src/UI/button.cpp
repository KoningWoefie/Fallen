#include <src/UI/button.h>
#include <src/Core/object.h>

namespace FallenUI
{
    Button::Button()
    {
        _width = 0;
        _height = 0;

    	_x = 0;
    	_y = 0;

    	_isHovered = false;
    	_isPressed = false;
    	_worldPosition = glm::vec2(0, 0);
    	_worldScale = glm::vec2(1, 1);

        std::cout << "Creating Button from default constructor" << "\n";
    }
    Button::Button(int width, int height)
    {
        _width = width;
        _height = height;

    	_x = 0;
    	_y = 0;

    	_isHovered = false;
    	_isPressed = false;
    	_worldPosition = glm::vec2(0, 0);
    	_worldScale = glm::vec2(1, 1);

        std::cout << "Creating Button from overloaded constructor" << "\n";
    }

    Button::~Button()
    {
        //dtor
    }

    void Button::UpdateState()
    {
        float x = _inputManager->GetMousePosition()[0];
        float y = _inputManager->GetMousePosition()[1];

        if(_isHovered && !_isPressed)
        {
            _isPressed = _inputManager->GetMouseButtonDown(0);
            if(_isPressed) _onPress();
        }
        if(_isPressed && _inputManager->GetMouseButtonUp(0))
        {
            _isPressed = false;
            _onRelease();
        }

        if(_x == x && _y == y) return;
        _x = x;
        _y = y;

        if(_x >= _worldPosition.x - ((float)_width * _worldScale.x)/2 && _x <= _worldPosition.x + ((float)_width * _worldScale.x)/2 && _y <= _worldPosition.y + ((float)_height*_worldScale.y)/2 && _y >= _worldPosition.y - ((float)_height*_worldScale.y)/2)
        {
            if(!_isHovered) _onHover();
            _isHovered = true;
        }
        else
        {
            _isHovered = false;
            _isPressed = false;
        }

    }

    void Button::Press()
    {
    	_isPressed = true;
    	_onPress();
    }

    void Button::Release()
    {
    	_isPressed = false;
    	_onRelease();
    }

    void Button::Select()
    {
    	_isHovered = true;
    	_onHover();
    }

    void Button::Deselect()
    {
    	_isHovered = false;
    }
}
