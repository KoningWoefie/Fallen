#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

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

    int round(float value);
    float round(float value, int decimals);
    double round(double value, int decimals);

    // solve linear equation x-axis intersection
    std::tuple<float, float> slex(float a, float b);
    // solve linear equation y-axis intersection
    std::tuple<float, float> sley(float a, float b);
    // solve linear equation point
    std::tuple<float, float> slep(float a, float b, float x);
    // solve linear equation intersections
    std::vector<std::tuple<float,float>> slei(float a, float b);

    // solve quadratic equation x-axis
    std::vector<std::tuple<float,float>> sqex(float a, float b, float c);
    // solve quadratic equation y-axis
    std::vector<std::tuple<float,float>> sqey(float a, float b, float c);
    // // solve quadratic equation point
    std::vector<std::tuple<float,float>> sqep(float a, float b, float c, float x);
    // // solve quadratic equation intersections
    // std::vector<std::tuple<float,float>> sqei(float a, float b, float c);

    
}

#endif