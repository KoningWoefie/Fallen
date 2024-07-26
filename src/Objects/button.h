#ifndef BUTTONPRESETS_H
#define BUTTONPRESETS_H

#include <src/Core/object.h>
#include <src/UI/button.h>
#include <src/Core/text.h>
#include <src/UI/image.h>

class Button : public Object
{
public:
    Button();
    Button(int width, int height);
    Button(int width, int height, std::string text);
    Button(std::string imagePath, int width, int height, std::string text);
    Button(std::string imagePath, int width, int height);
    Button(std::string imagePath, std::string text);
    Button(std::string imagePath);
    virtual ~Button();

    virtual void Update(float deltaTime);
private:
};

#endif // BUTTON_H
