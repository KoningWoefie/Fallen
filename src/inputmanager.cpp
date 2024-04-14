#include <src/inputmanager.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

InputManager::InputManager()
{
	_window = nullptr;
	std::cout << "creating inputmanager" << std::endl;
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

InputManager* InputManager::input()
{
	if (InputManager::_instance == nullptr)
	{
		_instance = new InputManager();
	}
	return _instance;
}

InputManager* InputManager::_instance = nullptr;
