#include "src/config.h"
#include <src/game.h>
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
	// this->UpdateDynamic(scene, dt);

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

void Game::UpdateDynamic(Dynamic* d, float deltaTime)
{
	d->update(deltaTime);

    // Update all the children of this dynamic as well
	for (Dynamic* cd : d->GetChildren())
	{
		UpdateDynamic(cd, deltaTime);
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
