#ifndef TESTOBJ_H
#define TESTOBJ_H

#include <src/object.h>
#include <src/image.h>

class TestObj : public Object
{
public:
    TestObj();
    virtual ~TestObj();
    virtual void Update(float deltaTime);

private:
};

#endif
