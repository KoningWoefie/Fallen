#ifndef EMPTYOBJECT_H
#define EMPTYOBJECT_H

#include <src/Core/object.h>

namespace Presets
{
    // Needs no cpp file because there is no implementation
    class EmptyObject : public Object
    {
    public:
        EmptyObject() { };
        virtual ~EmptyObject() { };

        virtual void Update(float deltaTime) { };
    private:
    };
}

#endif
