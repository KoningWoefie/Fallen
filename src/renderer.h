#ifndef RENDERER_H
#define RENDERER_H

#include <src/sprite.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <src/config.h>
#include <src/fontmanager.h>
#include <src/scene.h>
#include <src/resourcemanager.h>
#include <src/text.h>
#include <src/texture.h>
#include <src/mesh.h>
#include <src/object.h>
#include <src/image.h>
#include <src/canvas.h>

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    void RenderScene(Scene* scene);

    GLFWwindow* GetWindow() { return _window; }
    void SetWindow(GLFWwindow* window) { _window = window; }

    void ChangeScreenMode();
private:
    void RenderObject(Object* o, glm::mat4 PaMa);
    void RenderUIObject(Object* o, Canvas* canvas, glm::mat4 PaMa);

    void RenderImage(Image* i, glm::mat4 PaMa);
    void RenderText(Text* text, glm::mat4 PaMa);

    void RenderSprite(Sprite* sprite, glm::mat4 PaMa);
    void RenderSlicedSprite(SlicedSprite* i, glm::mat4 PaMa);

    int init();

	GLFWwindow* _window;
    ResourceManager _resMan;
    FontManager _fontMan;

	GLuint LoadShaders(
		const std::string& vertex_file_path,
		const std::string& fragment_file_path
	);

    GLuint ChooseShader(GLuint shaderID);

	GLuint _programID;
    GLuint _textShaderID;

    GLuint _activeID;

	Camera* _camera; // reference to scene->camera

	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;

    float _scaleX = 0;
    float _scaleY = 0;
};

#endif
