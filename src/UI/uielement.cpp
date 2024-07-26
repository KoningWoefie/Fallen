#include <src/UI/uielement.h>

namespace Components
{
    UIElement::UIElement(UIAlignment alignment)
    {
        _alignment = (int)alignment;
    }

    UIElement::~UIElement()
    {
    }
}
