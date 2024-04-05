#include "src/config.h"
#include <src/game.h>
#include "GLFW/glfw3.h"

Game::Game()
{
	running = true;
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
	glfwGetWindowSize(renderer.window(), &width, &height);

	Config::ScreenWidth = width;
	Config::ScreenHeight = height;

	//get deltaTime and update camera
	float dt = this->UpdateDeltaTime();
	scene->camera()->UpdateProjectionMatrix();
	scene->camera()->computeViewMatrixFromInput(renderer.window(), dt);

    // Update the input manager so it registers keys
	_inMan->update(renderer.window());

	// Update the scene
	// this->UpdateDynamic(scene, dt);

	// Render the scene
	renderer.RenderScene(scene);

    // Check if the game should still run
	if (glfwGetKey(renderer.window(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer.window()) == 0)
	{
		running = true;
	}
	else
	{
		running = false;
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
