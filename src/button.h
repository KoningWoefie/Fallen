#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <src/component.h>
#include <src/inputmanager.h>

class Button : public Component
{
public:
    Button();
    Button(int width, int height);
    virtual ~Button();

    int GetWidth() { return _width; }
    int GetHeight() { return _height; }
    glm::vec2 GetSize() { return glm::vec2(_width, _height); }

    void SetSize(int width, int height) { _width = width; _height = height; }

    void SetOnPress(std::function<void()> opf) { _onPress = opf; }
    void SetOnRelease(std::function<void()> orf) { _onRelease = orf; }
    void SetOnHover(std::function<void()> ohf) { _onHover = ohf; };

    void UpdateState();

    void SetWorldPosition(glm::vec2 worldPos) { _worldPosition = worldPos; }
    glm::vec2 GetWorldPosition() { return _worldPosition; }

    void SetWorldScale(glm::vec2 worldScale) { _worldScale = worldScale; }
    glm::vec2 GetWorldScale() { return _worldScale; }

	void Press();
	void Release();
	void Select();
	void Deselect();

private:
    int _width;
    int _height;

    float _x;
    float _y;

    glm::vec2 _worldPosition;
    glm::vec2 _worldScale;

    bool _isHovered;
    bool _isPressed;

    std::function<void()> _onPress;
    std::function<void()> _onRelease;
    std::function<void()> _onHover;

    InputManager* _inputManager = InputManager::input();
};

#endif
