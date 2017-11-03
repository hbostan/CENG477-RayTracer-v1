#ifndef __HW1__RAY__
#define __HW1__RAY__

#include "Vector.h"

class Ray
{
public:
    Ray(): origin(Point()), direction(Vec3f()){}
    Ray(const Ray &r): origin(r.origin), direction(r.direction){}
    Ray(Point origin, Vec3f direction): origin(origin), direction(direction){}

    Point origin;
    Vec3f direction;
	//TODO: Add reflection count here

    Point calculate(float t) 
    {
        return origin + direction * t;
    }
};

#endif