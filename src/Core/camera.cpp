#include <src/Core/config.h>
#include <src/Core/camera.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

Camera::Camera()
{
	_projectionMatrix = glm::ortho(0.0f, (float)Config::ScreenWidth, (float)Config::ScreenHeight, 0.0f, 0.1f, 100.0f);
	_viewMatrix = glm::mat4(1.0f);
	_cursor = glm::vec3( 0, 0, 0 );
}

Camera::~Camera()
{

}

void Camera::UpdateProjectionMatrix()
{
    _projectionMatrix = glm::ortho(0.0f, (float)Config::ScreenWidth, (float)Config::ScreenHeight, 0.0f, 0.1f, 100.0f);
}

void Camera::computeViewMatrixFromInput(GLFWwindow* window, float deltaTime)
{
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	_cursor = glm::vec3( xpos, ypos, 0 );

	static glm::vec3 position = glm::vec3( 0, 0, 10 ); // Initial position : on +Z

	// View matrix
	_viewMatrix = glm::lookAt(
			position, /* Camera is at (xpos,ypos,zpos), in World Space */
			position + glm::vec3(0, 0, -1), /* and looks towards Z */
			glm::vec3(0, 1, 0)  /* Head is up (set to 0,-1,0 to look upside-down) */
		);
}
