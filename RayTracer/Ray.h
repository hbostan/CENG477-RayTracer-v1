#ifndef __HW1__RAY__
#define __HW1__RAY__

#include "Vector.h"

class Ray
{
public:
    Ray(Point origin, Vec3f direction);

    Point origin;
    Vec3f direction;

    float distMin;
    float distMax;
};

#endif