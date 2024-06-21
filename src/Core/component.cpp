#include <src/Core/object.h>
#include <src/Core/component.h>

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
