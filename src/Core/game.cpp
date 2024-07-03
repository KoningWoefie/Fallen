#include "src/Core/config.h"
#include <src/Core/game.h>
#include "GLFW/glfw3.h"

Game::Game()
{
	_running = true;
}

Game::~Game()
{
}

void Game::Run(Scene* scene)
{
    if(Config::ChangedScreenMode)
    {
        renderer.ChangeScreenMode();
        Config::ChangedScreenMode = false;
    }
    if(Config::ChangedTitle)
    {
        glfwSetWindowTitle(renderer.GetWindow(), Config::GetTitle().c_str());
        Config::ChangedTitle = false;
    }
    int width, height;
	glfwGetWindowSize(renderer.GetWindow(), &width, &height);

	Config::ScreenWidth = width;
	Config::ScreenHeight = height;

	//get deltaTime and update camera
	float dt = this->UpdateDeltaTime();
	scene->GetCamera()->UpdateProjectionMatrix();
	scene->GetCamera()->computeViewMatrixFromInput(renderer.GetWindow(), dt);

    // Update the input manager so it registers keys
	_inMan->Update(renderer.GetWindow());

	// Update the scene
	this->UpdateObject(scene, dt);

	// Render the scene
	renderer.RenderScene(scene);

    // Check if the game should still run
	if (glfwGetKey(renderer.GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer.GetWindow()) == 0)
	{
		_running = true;
	}
	else
	{
		_running = false;
	}
}

void Game::UpdateObject(Object* o, float deltaTime)
{
	o->Update(deltaTime);

    // Update all the children of this dynamic as well
	for (Object* co : o->GetChildren())
	{
		UpdateObject(co, deltaTime);
	}
}

float Game::UpdateDeltaTime()
{
    // lastTime is initialised only the first time this function is called
	static double lastTime = glfwGetTime();
	// get the current time
	double currentTime = glfwGetTime();

	// Compute time difference between current and last time
	float deltaTime = float(currentTime - lastTime);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
	return deltaTime;
}
