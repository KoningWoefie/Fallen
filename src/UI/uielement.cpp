#include <src/UI/uielement.h>

namespace FallenUI
{
    UIElement::UIElement(UIAlignment alignment)
    {
        _alignment = (int)alignment;
    }

    UIElement::~UIElement()
    {
    }
}
