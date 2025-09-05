#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <iostream>

namespace FallenMath
{
    int pow(int base, int exp);
    float pow(float base, float exp);
    double pow(double base, double exp);

    float sqrt(int value);
    float sqrt(float value);
    double sqrt(double value);

    int lerp(int start, int end, float t);
    float lerp(float start, float end, float t);
    double lerp(double start, double end, float t);

    int clamp(int value, int min, int max);
    float clamp(float value, float min, float max);
    double clamp(double value, double min, double max);
}

#endif