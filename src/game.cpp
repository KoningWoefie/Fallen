#include <src/game.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

Game::Game() 
{
	running = true;
} 
Game::~Game() 
{
}

void Game::Run(Scene* scene)
{
	// get deltaTime and update camera
	float dt = this->updateDeltaTime();
	scene->camera()->computeViewMatrixFromInput(renderer.window(), dt);
	// _inMan->update(renderer.window());

	// Update the scene
	this->UpdateDynamic(scene, dt);

	// Render the scene
	renderer.RenderScene(scene);

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
	for (Dynamic* cd : d->GetChildren())
	{
		UpdateDynamic(cd, deltaTime);
	}
}

float Game::updateDeltaTime()
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