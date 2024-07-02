#ifndef EXAMPLESCENE00_H
#define EXAMPLESCENE00_H

#include <src/Core/scene.h>
#include <src/Core/sprite.h>
#include <src/Core/text.h>
#include <src/UI/canvas.h>
#include <src/Presets/button.h>
#include <src/Presets/canvas.h>
#include <src/Networking/sql.h>

class ExampleScene00 : public Scene
{
public:
    ExampleScene00();
    ~ExampleScene00();

    virtual void Update(float deltaTime);
private:
    Presets::Button* button;
    Presets::Canvas* canvas;

    void OnButtonClicked();
    void OnButtonHovered();
    void OnButtonReleased();

    void GetDatabaseValue();

    SQL* sql;

};


#endif
