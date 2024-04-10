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
    LeftBottom,
    RightBottom,
    LeftTop,
    RightTop,
};

class UIElement : public Component
{
public:
    UIElement(UIAlignment alignment = UIAlignment::Center);
    virtual ~UIElement();

    void SetAlignment(UIAlignment alignment) { _alignment = (int)alignment; };

private:
    int _alignment;

};
#endif
