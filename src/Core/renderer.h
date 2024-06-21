#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <src/Core/sprite.h>
#include <GLFW/glfw3.h>

#include <src/Core/config.h>
#include <src/Core/fontmanager.h>
#include <src/Core/scene.h>
#include <src/Core/resourcemanager.h>
#include <src/Core/text.h>
#include <src/Core/texture.h>
#include <src/Core/mesh.h>
#include <src/Core/object.h>
#include <src/UI/image.h>
#include <src/UI/canvas.h>
#include <src/UI/button.h>

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
    void RenderUIObject(Object* o, FallenUI::Canvas* canvas, glm::mat4 PaMa);

    void RenderImage(FallenUI::Image* i, glm::mat4 PaMa);
    void RenderText(Text* text, glm::mat4 PaMa);

    void RenderSprite(Sprite* sprite, glm::mat4 PaMa);
    void RenderSlicedSprite(SlicedSprite* i, glm::mat4 PaMa);
    void RenderSpriteSheet(SpriteSheet* ss, glm::mat4 PaMa);

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

    glm::vec2 _worldPos;
};

#endif
