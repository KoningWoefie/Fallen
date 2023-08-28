#ifndef EXAMPLESCENE00_H
#define EXAMPLESCENE00_H

#include <src/scene.h>
#include "SheetTest.h"

class ExampleScene00 : public Scene
{
public:
    ExampleScene00();
    ~ExampleScene00();

    virtual void update(float deltaTime);
private:
    SheetTest* st;
};


#endif