#include <src/object.h>
#include <src/component.h>

Component::Component()
{
	Renderable = false;
	object = nullptr;
    //ctor
}

Component::~Component()
{
    //dtor
}
