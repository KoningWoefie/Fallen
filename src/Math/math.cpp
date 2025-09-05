#include <src/Math/math.h>

namespace FallenMath
{
    int pow(int base, int exp) { return std::pow(base, exp); }
    float pow(float base, float exp) { return std::powf(base, exp); }
    double pow(double base, double exp) { return std::pow(base, exp); }

    float sqrt(int value) { return std::sqrt(value); }
    float sqrt(float value) { return std::sqrtf(value); }
    double sqrt(double value) { return std::sqrt(value); }

    int lerp(int start, int end, float time)
    {
        if (start == end) 
        {
            std::cout << "The start of this is equal to the end" << "\n";
            return -1;
        }

        return (end - start) * time + start;
    }

    float lerp(float start, float end, float time)
    {
        start = std::roundf(start*10000)/10000;
        end = std::roundf(end*10000)/10000;

        if (start == end) 
        {
            std::cout << "The start of this is equal to the end" << "\n";
            return -1;
        }

        return (end - start) * time + start;
    }

    double lerp(double start, double end, float time)
    {
        start = std::round(start*10000)/10000;
        end = std::round(end*10000)/10000;

        if (start == end) 
        {
            std::cout << "The start of this is equal to the end" << "\n";
            return -1;
        }

        return (end - start) * time + start;
    }

    int clamp(int value, int min, int max)
    {
        if(min > max)
        {
            std::cout << "the minimum is smaller than the maximum exiting" << "\n";
            return -1;
        }
        int clampedValue = 0;

        if (value < min) clampedValue = min;
        else if (value > max) clampedValue = max;
        else clampedValue = value;

        return clampedValue;
    }

    float clamp(float value, float min, float max)
    {
        if(min > max)
        {
            std::cout << "the minimum is smaller than the maximum exiting" << "\n";
            return -1;
        }
        float clampedValue = 0.0f;

        if (value < min) clampedValue = min;
        else if (value > max) clampedValue = max;
        else clampedValue = value;

        return clampedValue;
    }

    double clamp(double value, double min, double max)
    {
        if(min > max)
        {
            std::cout << "the minimum is smaller than the maximum exiting" << "\n";
            return -1;
        }
        double clampedValue = 0.0;

        if (value < min) clampedValue = min;
        else if (value > max) clampedValue = max;
        else clampedValue = value;

        return clampedValue;
    }
}