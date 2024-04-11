#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <src/component.h>

enum class UIAlignment
{
    Center,
    Left,
    Right,
    Top,
    Bottom,
    BottomLeft,
    BottomRight,
    TopLeft,
    TopRight,
};

class UIElement : public Component
{
public:
    UIElement(UIAlignment alignment = UIAlignment::Center);
    virtual ~UIElement();

    void SetAlignment(UIAlignment alignment) { _alignment = (int)alignment; };
    UIAlignment GetAlignment() { return (UIAlignment)_alignment; };

private:
    int _alignment;

};
#endif
