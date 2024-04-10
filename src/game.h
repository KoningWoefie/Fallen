#ifndef GAME_H
#define GAME_H

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <src/config.h>
#include <src/scene.h>
#include <src/renderer.h>
#include <src/camera.h>
#include <src/inputmanager.h>
#include <src/object.h>

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
