#ifndef EXAMPLESCENE00_H
#define EXAMPLESCENE00_H

#include <src/scene.h>
#include <src/sprite.h>
#include <src/text.h>
#include <src/canvas.h>
#include "testobj.h"

class ExampleScene00 : public Scene
{
public:
    ExampleScene00();
    ~ExampleScene00();

    virtual void Update(float deltaTime);
private:
    TestObj* testObj;
    TestObj* canvas;
};


#endif
