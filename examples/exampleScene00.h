#ifndef EXAMPLESCENE00_H
#define EXAMPLESCENE00_H

#include <src/scene.h>

class ExampleScene00 : public Scene
{
public:
    ExampleScene00(/* args */);
    ~ExampleScene00();

    virtual void update(float deltaTime);
};


#endif