#include <_ctype.h>
#include <src/Core/inputmanager.h>
#include "GLFW/glfw3.h"
#include <cctype>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

InputManager::InputManager()
{
	_window = nullptr;
	_mousePosition = glm::vec2(0, 0);
	std::cout << "creating inputmanager" << "\n";
}
InputManager::~InputManager()
{
}

void InputManager::Update(GLFWwindow* w)
{
	_window = w;

	double x = 0.0;
	double y = 0.0;

	glfwGetCursorPos(w, &x, &y);

	_mousePosition = glm::vec2(x, y);

	for (int i = 32; i < 96; i++)
	{
		RegisterKey(i, w);
	}

	for (unsigned int i = 256; i < GLFW_KEY_LAST; i++)
	{
		RegisterKey(i, w);
	}

	for (int i = 0; i < 8; i++)
	{
	   RegisterMouseButton(i, w);
	}
}

bool InputManager::GetKey(KeyCode k)
{
	return _keys[(int)k];
}
bool InputManager::GetKeyDown(KeyCode k)
{
	return _keysDown[(int)k];
}
bool InputManager::GetKeyUp(KeyCode k)
{
	return _keysUp[(int)k];
}

char InputManager::GetChar(KeyCode k)
{
    if(_keysDown[(int)k])
    {
        if(!_keys[int(KeyCode::LeftShift)]) return tolower((char)k);
        return (char)k;
    }

    return 0;
}

void InputManager::RegisterKey(int key, GLFWwindow* w)
{
	if (glfwGetKey(w, key) == GLFW_PRESS)
	{
		if (_keys[key] == false)
		{
			_keys[key] = true;
			_keysDown[key] = true;
		}
		else
		{
			_keysDown[key] = false;
		}
	}
	else
	{
		_keys[key] = false;
		_keysDown[key] = false;
		_keysUp[key] = false;
	}
	if (glfwGetKey(w, key) == GLFW_RELEASE)
	{
		if (_keys[key] == true)
		{
			_keys[key] = false;
			_keysUp[key] = true;
		}
		else
		{
			_keysUp[key] = false;
		}
	}
}

bool InputManager::GetMouseButton(int b)
{
    return _mouseButtons[b];
}
bool InputManager::GetMouseButtonDown(int b)
{
    return _mouseButtonsDown[b];
}
bool InputManager::GetMouseButtonUp(int b)
{
    return _mouseButtonsUp[b];
}

void InputManager::RegisterMouseButton(int button, GLFWwindow* w)
{
   	if (glfwGetMouseButton(w, button) == GLFW_PRESS)
	{
		if (_mouseButtons[button] == false)
		{
			_mouseButtons[button] = true;
			_mouseButtonsDown[button] = true;
		} else
		{
			_mouseButtonsDown[button] = false;
		}
	}

	if (glfwGetMouseButton(w, button) == GLFW_RELEASE)
	{
		if (_mouseButtons[button] == true)
		{
			_mouseButtons[button] = false;
			_mouseButtonsUp[button] = true;
	   	}
		else
	   	{
			_mouseButtonsUp[button] = false;
	   	}
	}
}



InputManager* InputManager::input()
{
	if (InputManager::_instance == nullptr)
	{
		_instance = new InputManager();
	}
	return _instance;
}

InputManager* InputManager::_instance = nullptr;
