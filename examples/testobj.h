#ifndef TESTOBJ_H
#define TESTOBJ_H

#include <src/Core/object.h>
#include <src/UI/image.h>

class TestObj : public Object
{
public:
    TestObj();
    virtual ~TestObj();
    virtual void Update(float deltaTime);

private:
};

#endif
