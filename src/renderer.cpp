#include <src/camera.h>
#include "GLFW/glfw3.h"
#include "src/inputmanager.h"
#include "src/sprite.h"
#include "src/uielement.h"
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
#include <src/renderer.h>

Renderer::Renderer()
{
    //get this in renderScene
    _camera = nullptr;
    _window = nullptr;

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

	// Red background
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

	// Backface culling
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	_programID = this->LoadShaders("shaders/sprite.vert", "shaders/sprite.frag");
	_textShaderID = this->LoadShaders("shaders/text.vert", "shaders/text.frag");

	// Use our shader
	glUseProgram(_programID);

	ChangeScreenMode();
	return 0;
}

void Renderer::ChangeScreenMode()
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    switch (Config::GetScreenMode())
    {
        case 0:
            glfwSetWindowMonitor(_window, nullptr, 0, 0, Config::ScreenWidth, Config::ScreenHeight, 60);
            break;
        case 1:
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            glfwSetWindowMonitor(_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

            break;
    }
}

void Renderer::RenderScene(Scene* scene)
{
    _camera = scene->GetCamera();

    _viewMatrix = _camera->GetViewMatrix();
	_projectionMatrix = _camera->GetProjectionMatrix();

    glm::mat4 im = glm::mat4(1.0f);

    //clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->RenderObject(scene, im);
    _scaleX = 1.0f;
    _scaleY = 1.0f;

    if(_window != nullptr) glfwSwapBuffers(this->GetWindow());
	glfwWaitEventsTimeout(0.07);
}

void Renderer::RenderObject(Object* o, glm::mat4 PaMa)
{
    _scaleX *= o->transform->scale.x;
    _scaleY *= o->transform->scale.y;

    _worldPos += glm::vec2(o->transform->position.x, o->transform->position.y);
    glm::vec2 thisWorldPos = _worldPos;

    float sX = _scaleX;
    float sY = _scaleY;

    //Build our model matrix
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(o->transform->position.x, o->transform->position.y, 0));
    glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, o->transform->rotation);
    glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(o->transform->scale.x, o->transform->scale.y, 1));
    glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

    PaMa *= modelMatrix;

    for(Component* c : o->GetComponents())
    {
        if(!c->isRenderable()) continue;
        auto& type = *c;
        if(typeid(type) == typeid(Image)) { RenderImage(dynamic_cast<Image*>(c), PaMa); }
        if(typeid(type) == typeid(Text)) { RenderText(dynamic_cast<Text*>(c), PaMa); }
        if(typeid(type) == typeid(Button))
        {
            Button* b = dynamic_cast<Button*>(c);
            b->SetWorldPosition(_worldPos);
            b->SetWorldScale(glm::vec2(_scaleX, _scaleY));
            b->UpdateState();
        }
    }
    for(Object* o2 : o->GetChildren())
    {
        Canvas* c = o->GetComponent<Canvas>();
        if(c)
        {
            if(c->GetScaleWithScreenSize())
            {
                c->SetCanvasSize(Config::ScreenWidth, Config::ScreenHeight);
                o->transform->position = glm::vec3(Config::ScreenWidth/2, Config::ScreenHeight/2, 0.0f);
            }
            RenderUIObject(o2, c, PaMa);
            c = nullptr;
            continue;
        }
        RenderObject(o2, PaMa);
    }
    _scaleX = sX;
    _scaleY = sY;
    _worldPos = thisWorldPos;
}

void Renderer::RenderUIObject(Object* o, Canvas* canvas, glm::mat4 PaMa)
{
    _scaleX *= o->transform->scale.x;
    _scaleY *= o->transform->scale.y;


    float sX = _scaleX;
    float sY = _scaleY;

    float x = 0;
    float y = 0;

    if(o->GetComponent<UIElement>() == nullptr)
    {
        std::cout << "UIElement component not found on object that is a child of canvas" << std::endl;
        return;
    }

    switch (o->GetComponent<UIElement>()->GetAlignment())
    {
        case UIAlignment::Center:
            x = 0;
            y = 0;
            break;
        case UIAlignment::TopLeft:
            x = -((float)(canvas->GetCanvasWidth()) / 2);
            y = -((float)(canvas->GetCanvasHeight()) / 2);
            break;
        case UIAlignment::Top:
            x = 0;
            y = -((float)(canvas->GetCanvasHeight()) / 2);
            break;
        case UIAlignment::TopRight:
            x = (float)canvas->GetCanvasWidth() / 2;
            y = -((float)(canvas->GetCanvasHeight()) / 2);
            break;
        case UIAlignment::Left:
            x = -((float)(canvas->GetCanvasWidth()) / 2);
            y = 0;
            break;
        case UIAlignment::Right:
            x = ((float)(canvas->GetCanvasWidth()) / 2);
            y = 0;
            break;
        case UIAlignment::BottomLeft:
            x = -((float)(canvas->GetCanvasWidth()) / 2);
            y = (float)(canvas->GetCanvasHeight()) / 2;
            break;
        case UIAlignment::Bottom:
            x = 0;
            y = (float)(canvas->GetCanvasHeight()) / 2;
            break;
        case UIAlignment::BottomRight:
            x = (float)canvas->GetCanvasWidth() / 2;
            y = (float)(canvas->GetCanvasHeight()) / 2;
            break;
    }

    _worldPos += glm::vec2(o->transform->position.x + x, o->transform->position.y + y);
    glm::vec2 thisWorldPos = _worldPos;

    float csX = (float)Config::ScreenWidth / (float)canvas->GetReferenceResolution().x;
    float csY = (float)Config::ScreenHeight / (float)canvas->GetReferenceResolution().y;
    float cs = (csX + csY) / 2;

    //Build our model matrix
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(o->transform->position.x + x, o->transform->position.y + y, 0));
    glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, o->transform->rotation);
    glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(o->transform->scale.x * cs, o->transform->scale.y * cs, 1));
    glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

    PaMa *= modelMatrix;

    _scaleX *= cs;
    _scaleY *= cs;

    for(Component* c : o->GetComponents())
    {
        auto& type = *c;
        if(typeid(type) == typeid(Button))
        {
            Button* b = dynamic_cast<Button*>(c);
            b->SetWorldPosition(_worldPos);
            b->SetWorldScale(glm::vec2(_scaleX, _scaleY));
            b->UpdateState();
        }
        if(typeid(type) == typeid(Image)) { RenderImage(dynamic_cast<Image*>(c), PaMa); }
        if(typeid(type) == typeid(Text)) { RenderText(dynamic_cast<Text*>(c), PaMa); }
    }
    for(Object* o2 : o->GetChildren())
    {
        RenderUIObject(o2, canvas, PaMa);
    }
    _scaleX = sX;
    _scaleY = sY;

    _worldPos = thisWorldPos;
}

void Renderer::RenderImage(Image* i, glm::mat4 PaMa)
{
    this->ChooseShader(_programID);

    glActiveTexture(GL_TEXTURE0);

    // Set the color you want your texture to be blended with
    GLuint colorID = glGetUniformLocation(_programID, "blendColor");
	glUniform4f(colorID, i->color.r/255.0f, i->color.g/255.0f, i->color.b/255.0f, i->color.a/255.0f);

    if(i->GetSprite())
    {
        switch(i->GetSprite()->Type())
        {
            case 0:
                RenderSprite(i->GetSprite(), PaMa);
                break;
            case 1:
                RenderSlicedSprite(dynamic_cast<SlicedSprite*>(i->GetSprite()), PaMa);
                break;
            case 2:
                RenderSpriteSheet(dynamic_cast<SpriteSheet*>(i->GetSprite()), PaMa);
                break;
            default:
                break;
        }
        return;
    }

    glm::mat4 MVP = _projectionMatrix * _viewMatrix * PaMa;
    Mesh* m = _resMan.GetMesh(i->width, i->height, 0, i->pivot);

    GLuint dColorID = glGetUniformLocation(_programID, "defaultColor");
	glUniform4f(dColorID, 255.0f, 255.0f, 255.0f, 255.0f);

    // Set UVoffset in the shader (not relevant yet)
	GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
	glUniform2f(uvOffset, 0, 0);


    // Set the Model, View, Projection matrix in the shader
    GLuint matrixID = glGetUniformLocation(_programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1st attribute buffer : vertices
	GLuint vertexPositionID = glGetAttribLocation(_programID, "vertexPosition");
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, m->GetVertexBuffer());
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
	glBindBuffer(GL_ARRAY_BUFFER, m->GetUVBuffer());
	glVertexAttribPointer(
		vertexUVID, // The attribute we want to configure
		2,          // size : U,V => 2
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, m->GetNumverts());

	// cleanup
	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
}


void Renderer::RenderSprite(Sprite* s, glm::mat4 PaMa)
{
    glm::mat4 MVP = _projectionMatrix * _viewMatrix * PaMa;

    glActiveTexture(GL_TEXTURE0);
    Texture* t = _resMan.GetTexture(s->FileName());

    glBindTexture(GL_TEXTURE_2D, t->GetTexture());

    GLuint textureID = glGetUniformLocation(_programID, "textureSampler");
    glUniform1i(textureID, 0);

    Mesh* m = _resMan.GetMesh(t->Width(), t->Height(), 0, glm::vec2(0.5f, 0.5f));

    GLuint dColorID = glGetUniformLocation(_programID, "defaultColor");

    glUniform4f(dColorID, 0.0f, 0.0f, 0.0f, 0.0f);

    // Set UVoffset in the shader not relevant here
	GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
	glUniform2f(uvOffset, 0, 0);

    // Set the Model, View, Projection matrix in the shader
    GLuint matrixID = glGetUniformLocation(_programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1st attribute buffer : vertices
	GLuint vertexPositionID = glGetAttribLocation(_programID, "vertexPosition");
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, m->GetVertexBuffer());
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
	glBindBuffer(GL_ARRAY_BUFFER, m->GetUVBuffer());
	glVertexAttribPointer(
		vertexUVID, // The attribute we want to configure
		2,          // size : U,V => 2
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, m->GetNumverts());

	// cleanup
	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
}

void Renderer::RenderSlicedSprite(SlicedSprite* ss, glm::mat4 PaMa)
{
   	// Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
	Texture* t = _resMan.GetTexture(ss->FileName());

    ss->ChangeMeshData(t->Width(), t->Height());
    // Bind texture for OpenGL
	glBindTexture(GL_TEXTURE_2D, t->GetTexture());

	// Set our "textureSampler" sampler to use Texture Unit 0
	GLuint textureID = glGetUniformLocation(_programID, "textureSampler");
	glUniform1i(textureID, 0);

    // Set default color
    GLuint dColorID = glGetUniformLocation(_programID, "defaultColor");
	glUniform4f(dColorID, 0.0f, 0.0f, 0.0f, 0.0f);


	for (int i = 0; i < ss->GetMeshData().size(); i++)
	{
		float x = 0;
		float y = 0;

		// corrects the difference of scale so that the pixel size lines up with the texture size
		float sX = (t->Width() * _scaleX - ss->GetMeshData()[1].width - ss->GetMeshData()[2].width) / (ss->GetMeshData()[0].width * _scaleX);
		float sY = (t->Height() * _scaleY - ss->GetMeshData()[3].height - ss->GetMeshData()[4].height) / (ss->GetMeshData()[0].height * _scaleY);

		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		switch(i)
		{
			case 0:
			    //center
			    scale = glm::vec3(sX, sY, 1.0f);
				break;
			case 1:
				//left
				x = -((ss->GetMeshData()[0].width * sX / 2.0f) + (ss->GetMeshData()[i].width / 2.0f) / _scaleX);
				scale = glm::vec3(1/_scaleX, sY, 1);
				break;
			case 2:
				//right
				x = ((ss->GetMeshData()[0].width * sX / 2.0f) + (ss->GetMeshData()[i].width / 2.0f)/_scaleX);
				scale = glm::vec3(1/_scaleX, sY, 1);
				break;
			case 3:
				//top
				y = -(((ss->GetMeshData()[0].height * sY) / 2.0f) + ((ss->GetMeshData()[i].height / 2.0f) / _scaleY));
				scale = glm::vec3(sX, 1/_scaleY, 1);
				break;
			case 4:
				//bottom
				y = ((ss->GetMeshData()[0].height * sY) / 2.0f) + ((ss->GetMeshData()[i].height / 2.0f) / _scaleY);
				scale = glm::vec3(sX, 1/_scaleY, 1);
				break;
			case 5:
				//top left
				x = -((ss->GetMeshData()[0].width * sX / 2.0f) + (ss->GetMeshData()[i].width / 2.0f)/_scaleX);
				y = -(((ss->GetMeshData()[0].height * sY) / 2.0f) + ((ss->GetMeshData()[i].height / 2.0f) / _scaleY));
				scale = glm::vec3(1/_scaleX, 1/_scaleY, 1);
				break;
			case 6:
				//top right
				x = (ss->GetMeshData()[0].width * sX / 2.0f) + (ss->GetMeshData()[i].width / 2.0f)/_scaleX;
				y = -(((ss->GetMeshData()[0].height * sY) / 2.0f) + ((ss->GetMeshData()[i].height / 2.0f) / _scaleY));
				scale = glm::vec3(1/_scaleX, 1/_scaleY, 1);
				break;
			case 7:
				//bottom left
				x = -((ss->GetMeshData()[0].width * sX / 2.0f) + (ss->GetMeshData()[i].width / 2.0f)/_scaleX);
				y = (ss->GetMeshData()[0].height * sY / 2.0f) + (ss->GetMeshData()[i].height / 2.0f) / _scaleY;
				scale = glm::vec3(1/_scaleX, 1/_scaleY, 1);
				break;
			case 8:
				//bottom right
				x = (ss->GetMeshData()[0].width * sX / 2.0f) + (ss->GetMeshData()[i].width / 2.0f)/_scaleX;
				y = ((ss->GetMeshData()[0].height * sY) / 2.0f) + ((ss->GetMeshData()[i].height / 2.0f) / _scaleY);
				scale = glm::vec3(1/_scaleX, 1/_scaleY, 1);
				break;
			default:
				break;
		}
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
		glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, 0.0f);
		glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), scale);
		glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

		glm::mat4 mdm = PaMa;
		mdm *= modelMatrix;
		glm::mat4 MVP = _projectionMatrix * _viewMatrix * mdm;

		meshData md = ss->GetMeshData()[i];
		Mesh* m = _resMan.GetMesh(md.width, md.height, md.radius, md.pivot, md.uvWidth, md.uvHeight, false, true);

		// Set UVoffset in the shader (not relevant yet)
		GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
		glUniform2f(uvOffset, md.uvOffsetX, md.uvOffsetY);

       	// Set the Model, View, Projection matrix in the shader
       	GLuint matrixID = glGetUniformLocation(_programID, "MVP");
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1st attribute buffer : vertices
		GLuint vertexPositionID = glGetAttribLocation(_programID, "vertexPosition");
		glEnableVertexAttribArray(vertexPositionID);
		glBindBuffer(GL_ARRAY_BUFFER, m->GetVertexBuffer());
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
		glBindBuffer(GL_ARRAY_BUFFER, m->GetUVBuffer());
		glVertexAttribPointer(
			vertexUVID, // The attribute we want to configure
			2,          // size : U,V => 2
			GL_FLOAT,   // type
			GL_FALSE,   // normalized?
			0,          // stride
			(void*)0    // array buffer offset
		);

		// Draw the triangles
		glDrawArrays(GL_TRIANGLES, 0, m->GetNumverts());

		// cleanup
		glDisableVertexAttribArray(vertexPositionID);
		glDisableVertexAttribArray(vertexUVID);
	}
}

void Renderer::RenderSpriteSheet(SpriteSheet* ss, glm::mat4 PaMa)
{
    glm::mat4 MVP = _projectionMatrix * _viewMatrix * PaMa;

    glActiveTexture(GL_TEXTURE0);
    Texture* t = _resMan.GetTexture(ss->FileName());

    glBindTexture(GL_TEXTURE_2D, t->GetTexture());

    GLuint textureID = glGetUniformLocation(_programID, "textureSampler");
    glUniform1i(textureID, 0);

    Mesh* m = _resMan.GetMesh(t->Width(), t->Height(), 0, glm::vec2(0.5f, 0.5f), ss->GetUVWidth(), ss->GetUVHeight());

    GLuint dColorID = glGetUniformLocation(_programID, "defaultColor");

    glUniform4f(dColorID, 0.0f, 0.0f, 0.0f, 0.0f);

    // Set UVoffset in the shader not relevant here
	GLuint uvOffset = glGetUniformLocation(_programID, "UVoffset");
	glUniform2f(uvOffset, ss->GetUVOffset().x, ss->GetUVOffset().y);

    // Set the Model, View, Projection matrix in the shader
    GLuint matrixID = glGetUniformLocation(_programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1st attribute buffer : vertices
	GLuint vertexPositionID = glGetAttribLocation(_programID, "vertexPosition");
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, m->GetVertexBuffer());
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
	glBindBuffer(GL_ARRAY_BUFFER, m->GetUVBuffer());
	glVertexAttribPointer(
		vertexUVID, // The attribute we want to configure
		2,          // size : U,V => 2
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, m->GetNumverts());

	// cleanup
	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
}

void Renderer::RenderText(Text* text, glm::mat4 PaMa)
{
    this->ChooseShader(_textShaderID);
    float bigHeight = 0;
    float x = 0;
    float y = 0;
    for (int i = 0; i < text->text.size(); i++)
    {
        char g = text->text[i];
        glyph* gl = _fontMan.GetFont(text->GetFontName(), text->GetSize())[g];
        if((gl->size.y - gl->bearing.y) > bigHeight)
        {
            bigHeight = gl->size.y;
        }
    }
    for (int i = 0; i < text->text.size(); i++)
    {
        glm::mat4 TempPaMa = PaMa;
        char g = text->text[i];
        glyph* gl = _fontMan.GetFont(text->GetFontName(), text->GetSize())[g];
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

        Mesh* mesh = _resMan.GetMesh(width, height, 0, text->pivot, 1.0f, 1.0f, true);
        // Build MVP matrix
        // Send our transformation to the currently bound shader, in the "MVP" uniform
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 0));
        glm::mat4 rotationMatrix = glm::eulerAngleYXZ(0.0f, 0.0f, 0.0f);
        glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

        TempPaMa *= modelMatrix;

        glm::mat4 MVP = _projectionMatrix * _viewMatrix * TempPaMa;

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
        glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVertexBuffer());

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
        glBindBuffer(GL_ARRAY_BUFFER, mesh->GetUVBuffer());
        glVertexAttribPointer(
            vertexUVID, // The attribute we want to configure
            2,          // size : U,V => 2
            GL_FLOAT,   // type
            GL_FALSE,   // normalized?
            0,          // stride
            (void*)0    // array buffer offset
        );

        // Draw the triangles
        glDrawArrays(GL_TRIANGLES, 0, mesh->GetNumverts());

        // cleanup
        glDisableVertexAttribArray(vertexPositionID);
        glDisableVertexAttribArray(vertexUVID);

        x += (gl->advance >> 6);
    }
}

GLuint Renderer::LoadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path)
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

GLuint Renderer::ChooseShader(GLuint shaderID)
{
    if(_activeID == shaderID)
    {
        return _activeID;
    }
    glUseProgram(shaderID);
    _activeID = shaderID;
    return _activeID;
}
