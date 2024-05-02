#ifndef DEFAULTOBJECT_H
#define DEFAULTOBJECT_H

#include <src/object.h>
#include <src/image.h>

class DefaultObject : public Object
{
public:
	DefaultObject();
    virtual ~DefaultObject();
    void Update(float deltaTime);
private:
};

#endif
