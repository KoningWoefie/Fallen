#ifndef GAME_H
#define GAME_H

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <src/Core/config.h>
#include <src/Core/scene.h>
#include <src/Core/renderer.h>
#include <src/Core/camera.h>
#include <src/Core/inputmanager.h>
#include <src/Core/object.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

class Game
{
public:
    Game();
    virtual ~Game();

	void Run(Scene* scene);

	bool IsRunning() { return _running; }

private:
	Renderer renderer;

    float UpdateDeltaTime();

	void UpdateObject(Object* d, float deltaTime);

	InputManager* _inMan = InputManager::input();
	bool _running;
};

#endif // game_H
