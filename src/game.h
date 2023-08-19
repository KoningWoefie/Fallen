#ifndef GAME_H 
#define GAME_H

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <src/config.h>
#include <src/renderer.h>
#include <src/camera.h>
#include <src/inputmanager.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

class Game 
{ 
public: 
    Game(); 
    virtual ~Game();

	void Run(Scene* scene);

	bool IsRunning() { return running; }

private:
	Renderer renderer;

    float updateDeltaTime();

	void UpdateDynamic(Dynamic* e, float deltaTime);

	bool running;
}; 

#endif // game_H 