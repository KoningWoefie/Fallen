#ifndef EXAMPLESCENE00_H
#define EXAMPLESCENE00_H

#include <src/Core/scene.h>
#include <src/Core/sprite.h>
#include <src/Core/text.h>
#include <src/UI/canvas.h>
#include <src/Objects/button.h>
#include <src/Networking/sql.h>

class ExampleScene00 : public Scene
{
public:
    ExampleScene00();
    ~ExampleScene00();

    virtual void Update(float deltaTime);

    virtual void Initialize();
private:
    Button* button;

    void OnButtonClicked();
    void OnButtonHovered();
    void OnButtonReleased();

    void GetDatabaseValue();

    SQL* sql;

};


#endif
