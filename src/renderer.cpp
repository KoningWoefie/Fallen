#include <src/renderer.h>

Renderer::Renderer()
{
    //get this in renderScene
    _camera = nullptr;

    _viewMatrix = glm::mat4(1.0f);
	_projectionMatrix = glm::mat4(1.0f);

    //do some OpenGL things
	this->init();
}

Renderer::~Renderer()
{
    // Cleanup VBO and shader
	glDeleteProgram(_programID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

int Renderer::init()
{
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	// Set OpenGL version (2.1)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Open a window and create its OpenGL context
	_window = glfwCreateWindow( SWIDTH, SHEIGHT, "examples", NULL, NULL);
	if( _window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	_programID = this->loadShaders("shaders/sprite.vert", "shaders/sprite.frag");

	// Use our shader
	glUseProgram(_programID);

	return 0;
}

void Renderer::RenderScene(Scene* scene)
{
    _camera = scene->camera();

    _viewMatrix = _camera->getViewMatrix();
	_projectionMatrix = _camera->getProjectionMatrix();

    glm::mat4 im = glm::mat4(1.0f);

    //clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->RenderDynamic(scene, im);

    glfwSwapBuffers(this->window());
	glfwPollEvents();
}

void Renderer::RenderDynamic(Dynamic* d, glm::mat4 PaMa)
{
    // Build the Model matrix from Dynamic transform
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(d->position));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, d->rotation);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(d->scale.x, d->scale.y, d->scale.z));

	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	PaMa *= modelMatrix;
}