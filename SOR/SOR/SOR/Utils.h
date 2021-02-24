#pragma once

#include <math.h>

#define EPSILON    (1.0E-8)

namespace SOR
{
    static bool cmp_epsilon(float a, float b)
    {
        return fabs(a - b) < EPSILON;
    }

    static bool cmp_epsilon(double a, double b)
    {
        return fabs(a - b) < EPSILON;
    }
}
