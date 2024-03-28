#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include <src/config.h>
#include <src/camera.h>
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

	// Open a fullscreen window
	// GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	// const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	// glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	// glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	// glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	// glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	// _window = glfwCreateWindow(mode->width, mode->height, Config::Title.c_str(), monitor, NULL);

	// Set OpenGL version (2.1)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 4);

	_window = glfwCreateWindow(Config::ScreenWidth, Config::ScreenHeight, Config::Title.c_str(), NULL, NULL);

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
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	_programID = this->loadShaders("shaders/sprite.vert", "shaders/sprite.frag");
	_textShaderID = this->loadShaders("shaders/text.vert", "shaders/text.frag");

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
    this->chooseShader(_programID);

	scaleX += d->scale[0];
	scaleY += d->scale[1];

    // Build MVP matrix
	// Send our transformation to the currently bound shader, in the "MVP" uniform
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(d->position[0], d->position[1], 0));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, d->rotation);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(d->scale[0], d->scale[1], 1));
	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	// glm::mat4 mdm = PaMa;
	PaMa *= modelMatrix;
	glm::mat4 MVP = _projectionMatrix * _viewMatrix * PaMa;

	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
	Texture* t = _resMan.GetTexture(d->FileName());
	Mesh* m = nullptr;

    // If texture exists
    if(t)
    {
        // Bind texture for OpenGL
	    glBindTexture(GL_TEXTURE_2D, t->getTexture());

	    // Set our "textureSampler" sampler to use Texture Unit 0
	    GLuint textureID = glGetUniformLocation(_programID, "textureSampler");
	    glUniform1i(textureID, 0);

        // Get mesh with texture width and height
        m = _resMan.GetMesh(t->Width(), t->Height(), d->Radius(), d->Pivot(), d->UVWidth(), d->UVHeight());

        // Set default color
        GLuint dColorID = glGetUniformLocation(_programID, "defaultColor");
	    glUniform4f(dColorID, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    else
    {
        // Get mesh with the dynamic's width and height
        m = _resMan.GetMesh(d->Width(), d->Height(), d->Radius(), d->Pivot());

        // Set default color
        GLuint dColorID = glGetUniformLocation(_programID, "defaultColor");
	    glUniform4f(dColorID, 255.0f, 255.0f, 255.0f, 255.0f);
    }

    // Set UVoffset in the shader (not relevant yet)
	GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
	glUniform2f(uvOffset, d->UVOffset().x, d->UVOffset().y);

    // Set the color you want your texture to be blended with
    GLuint colorID = glGetUniformLocation(_programID, "blendColor");
	glUniform4f(colorID, d->color.r/255.0f, d->color.g/255.0f, d->color.b/255.0f, d->color.a/255.0f);

    // Set the Model, View, Projection matrix in the shader
    GLuint matrixID = glGetUniformLocation(_programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1st attribute buffer : vertices
	GLuint vertexPositionID = glGetAttribLocation(_programID, "vertexPosition");
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, m->vertexbuffer());
	glVertexAttribPointer(
		vertexPositionID, // The attribute we want to configure
		3,          // size : x,y,z => 3
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// 2nd attribute buffer : UVs
	GLuint vertexUVID = glGetAttribLocation(_programID, "vertexUV");
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, m->uvbuffer());
	glVertexAttribPointer(
		vertexUVID, // The attribute we want to configure
		2,          // size : U,V => 2
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, m->numverts());

	// cleanup
	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);

    if(d->text())
    {
        RenderText(d->text(), PaMa);
    }


    for (int i = 0; i < d->GetChildren().size(); i++)
    {
		if(d->GetChildren()[i]->Type() == 1)
		{
			RenderNineSlices((UISprite*)d->GetChildren()[i], PaMa);
			continue;
		}
        RenderDynamic(d->GetChildren()[i], PaMa);
    }
	scaleX = 0;
	scaleY = 0;
}

void Renderer::RenderNineSlices(UISprite* sprite, glm::mat4 PaMa)
{
	this->chooseShader(_programID);

	scaleX += sprite->scale[0];
	scaleY += sprite->scale[1];


	// Build MVP matrix
	// Send our transformation to the currently bound shader, in the "MVP" uniform
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(sprite->position[0], sprite->position[1], 0));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, sprite->rotation);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sprite->scale[0], sprite->scale[1], 1));
	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	// glm::mat4 mdm = PaMa;
	PaMa *= modelMatrix;

	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
	Texture* t = _resMan.GetTexture(sprite->FileName());
	// If texture exists
    if(t)
    {
		sprite->changeMeshData(t->Width(), t->Height());
        // Bind texture for OpenGL
	    glBindTexture(GL_TEXTURE_2D, t->getTexture());

	    // Set our "textureSampler" sampler to use Texture Unit 0
	    GLuint textureID = glGetUniformLocation(_programID, "textureSampler");
	    glUniform1i(textureID, 0);

        // Set default color
        GLuint dColorID = glGetUniformLocation(_programID, "defaultColor");
	    glUniform4f(dColorID, 0.0f, 0.0f, 0.0f, 0.0f);
    }
	for (int i = 0; i < sprite->GetMeshData().size(); i++)
	{
		float x = 0;
		float y = 0;

		// corrects the difference of scale so that the pixel size lines up with the texture size
		float sX = (t->Width() * scaleX - sprite->GetMeshData()[1].width - sprite->GetMeshData()[2].width) / (sprite->GetMeshData()[0].width * scaleX);
		float sY = (t->Height() * scaleY - sprite->GetMeshData()[3].height - sprite->GetMeshData()[4].height) / (sprite->GetMeshData()[0].height * scaleY);

		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		switch(i)
		{
			case 0:
			    //center
			    scale = glm::vec3(sX, sY, 1.0f);
				break;
			case 1:
				//left
				x = -((sprite->GetMeshData()[0].width * sX / 2.0f) + (sprite->GetMeshData()[i].width / 2.0f) / scaleX);
				scale = glm::vec3(1/scaleX, sY, 1);
				break;
			case 2:
				//right
				x = ((sprite->GetMeshData()[0].width * sX / 2.0f) + (sprite->GetMeshData()[i].width / 2.0f)/scaleX);
				scale = glm::vec3(1/scaleX, sY, 1);
				break;
			case 3:
				//top
				y = -(((sprite->GetMeshData()[0].height * sY) / 2.0f) + ((sprite->GetMeshData()[i].height / 2.0f) / scaleY));
				scale = glm::vec3(sX, 1/scaleY, 1);
				break;
			case 4:
				//bottom
				y = ((sprite->GetMeshData()[0].height * sY) / 2.0f) + ((sprite->GetMeshData()[i].height / 2.0f) / scaleY);
				scale = glm::vec3(sX, 1/scaleY, 1);
				break;
			case 5:
				//top left
				x = -((sprite->GetMeshData()[0].width * sX / 2.0f) + (sprite->GetMeshData()[i].width / 2.0f)/scaleX);
				y = -(((sprite->GetMeshData()[0].height * sY) / 2.0f) + ((sprite->GetMeshData()[i].height / 2.0f) / scaleY));
				scale = glm::vec3(1/scaleX, 1/scaleY, 1);
				break;
			case 6:
				//top right
				x = (sprite->GetMeshData()[0].width * sX / 2.0f) + (sprite->GetMeshData()[i].width / 2.0f)/scaleX;
				y = -(((sprite->GetMeshData()[0].height * sY) / 2.0f) + ((sprite->GetMeshData()[i].height / 2.0f) / scaleY));
				scale = glm::vec3(1/scaleX, 1/scaleY, 1);
				break;
			case 7:
				//bottom left
				x = -((sprite->GetMeshData()[0].width * sX / 2.0f) + (sprite->GetMeshData()[i].width / 2.0f)/scaleX);
				y = (sprite->GetMeshData()[0].height * sY / 2.0f) + (sprite->GetMeshData()[i].height / 2.0f) / scaleY;
				scale = glm::vec3(1/scaleX, 1/scaleY, 1);
				break;
			case 8:
				//bottom right
				x = (sprite->GetMeshData()[0].width * sX / 2.0f) + (sprite->GetMeshData()[i].width / 2.0f)/scaleX;
				y = ((sprite->GetMeshData()[0].height * sY) / 2.0f) + ((sprite->GetMeshData()[i].height / 2.0f) / scaleY);
				scale = glm::vec3(1/scaleX, 1/scaleY, 1);
				break;
			default:
				break;
		}
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
		glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, sprite->rotation);
		glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), scale);
		glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

		glm::mat4 mdm = PaMa;
		mdm *= modelMatrix;
		glm::mat4 MVP = _projectionMatrix * _viewMatrix * mdm;

		meshData md = sprite->GetMeshData()[i];
		Mesh* m = _resMan.GetMesh(md.width, md.height, md.radius, md.pivot, md.uvWidth, md.uvHeight, true);

		// Set UVoffset in the shader (not relevant yet)
		GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
		glUniform2f(uvOffset, md.uvOffsetX, md.uvOffsetY);

    	// Set the color you want your texture to be blended with
    	GLuint colorID = glGetUniformLocation(_programID, "blendColor");
		glUniform4f(colorID, sprite->color.r/255.0f, sprite->color.g/255.0f, sprite->color.b/255.0f, sprite->color.a/255.0f);

    	// Set the Model, View, Projection matrix in the shader
    	GLuint matrixID = glGetUniformLocation(_programID, "MVP");
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1st attribute buffer : vertices
		GLuint vertexPositionID = glGetAttribLocation(_programID, "vertexPosition");
		glEnableVertexAttribArray(vertexPositionID);
		glBindBuffer(GL_ARRAY_BUFFER, m->vertexbuffer());
		glVertexAttribPointer(
			vertexPositionID, // The attribute we want to configure
			3,          // size : x,y,z => 3
			GL_FLOAT,   // type
			GL_FALSE,   // normalized?
			0,          // stride
			(void*)0    // array buffer offset
		);

		// 2nd attribute buffer : UVs
		GLuint vertexUVID = glGetAttribLocation(_programID, "vertexUV");
		glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER, m->uvbuffer());
		glVertexAttribPointer(
			vertexUVID, // The attribute we want to configure
			2,          // size : U,V => 2
			GL_FLOAT,   // type
			GL_FALSE,   // normalized?
			0,          // stride
			(void*)0    // array buffer offset
		);

		// Draw the triangles
		glDrawArrays(GL_TRIANGLES, 0, m->numverts());

		// cleanup
		glDisableVertexAttribArray(vertexPositionID);
		glDisableVertexAttribArray(vertexUVID);
	}

    if(sprite->text())
    {
        RenderText(sprite->text(), PaMa);
    }

    for (int i = 0; i < sprite->GetChildren().size(); i++)
    {
		if(sprite->GetChildren()[i]->Type() == 1)
		{
			RenderNineSlices((UISprite*)sprite->GetChildren()[i], PaMa);
			continue;
		}
        RenderDynamic(sprite->GetChildren()[i], PaMa);
    }
	scaleX = 0;
	scaleY = 0;
}

void Renderer::RenderText(Text* text, glm::mat4 PaMa)
{
    this->chooseShader(_textShaderID);
    float bigHeight = 0;
    float x = 0;
    float y = 0;
    for (int i = 0; i < text->GetMessage().size(); i++)
    {
        char g = text->GetMessage()[i];
        glyph* gl = _fontMan.getFont(text->GetFontName(), text->GetSize())[g];
        if((gl->size.y - gl->bearing.y) > bigHeight)
        {
            bigHeight = gl->size.y;
        }
    }
    for (int i = 0; i < text->GetMessage().size(); i++)
    {
        glm::mat4 pama = PaMa;
        char g = text->GetMessage()[i];
        glyph* gl = _fontMan.getFont(text->GetFontName(), text->GetSize())[g];
        float posX = 0 + gl->size.x * text->pivot.x;
        if(x)
        {
            posX = x + gl->bearing.x;
        }
        else
        {
            x += gl->size.x * text->pivot.x;
        }
        float posY = (y - gl->bearing.y) + (bigHeight + (gl->size.y * text->pivot.y));

        float width = gl->size.x;
        float height = gl->size.y;

        Mesh* mesh = _resMan.GetMesh(width, height, 0, text->pivot, 1.0f, 1.0f);
        // Build MVP matrix
        // Send our transformation to the currently bound shader, in the "MVP" uniform
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 0));
        glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, 0.0f);
        glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

        pama *= modelMatrix;

        glm::mat4 MVP = _projectionMatrix * _viewMatrix * pama;

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gl->texture);

        // Set our "textureSampler" sampler to use Texture Unit 0
        GLuint textureID = glGetUniformLocation(_textShaderID, "textureSampler");
        glUniform1i(textureID, 0);

        // Set UVoffset in the shader
        GLuint uvOffset = glGetUniformLocation(_textShaderID, "UVoffset");
        glUniform2f(uvOffset, 0.0f, 0.0f);

        // Set the default color
        // GLuint dColorID = glGetUniformLocation(_textShaderID, "defaultColor");
        // glUniform4f(dColorID, 255.0f, 255.0f, 255.0f, 255.0f);

        // Set the color you want your texture to be blended with
        GLuint colorID = glGetUniformLocation(_textShaderID, "textColor");
        glUniform4f(colorID, text->color.r, text->color.g, text->color.b, text->color.a);

        // Set the Model, View, Projection matrix in the shader
        GLuint matrixID = glGetUniformLocation(_textShaderID, "MVP");
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

        // 1st attribute buffer : vertices
        GLuint vertexPositionID = glGetAttribLocation(_textShaderID, "vertexPosition");
        glEnableVertexAttribArray(vertexPositionID);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbuffer());

        glVertexAttribPointer(
            vertexPositionID, // The attribute we want to configure
            3,          // size : x,y,z => 3
            GL_FLOAT,   // type
            GL_FALSE,   // normalized?
            0,          // stride
            (void*)0    // array buffer offset
        );

        // 2nd attribute buffer : UVs
        GLuint vertexUVID = glGetAttribLocation(_textShaderID, "vertexUV");
        glEnableVertexAttribArray(vertexUVID);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->uvbuffer());
        glVertexAttribPointer(
            vertexUVID, // The attribute we want to configure
            2,          // size : U,V => 2
            GL_FLOAT,   // type
            GL_FALSE,   // normalized?
            0,          // stride
            (void*)0    // array buffer offset
        );

        // Draw the triangles
        glDrawArrays(GL_TRIANGLES, 0, mesh->numverts());

        // cleanup
        glDisableVertexAttribArray(vertexPositionID);
        glDisableVertexAttribArray(vertexUVID);

        x += (gl->advance >> 6);
    }
}

GLuint Renderer::loadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertex_file_path.c_str(), std::ios::in);
	if (vertexShaderStream.is_open()){
		std::string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	} else {
		printf("Can't to open %s.\n", vertex_file_path.c_str());
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragment_file_path.c_str(), std::ios::in);
	if (fragmentShaderStream.is_open()){
		std::string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	} else {
		printf("Can't to open %s.\n", fragment_file_path.c_str());
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path.c_str());
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer , NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path.c_str());
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> programErrorMessage(infoLogLength+1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

GLuint Renderer::chooseShader(GLuint shaderID)
{
    if(_activeID == shaderID)
    {
        return _activeID;
    }
    glUseProgram(shaderID);
    _activeID = shaderID;
    return _activeID;
}
