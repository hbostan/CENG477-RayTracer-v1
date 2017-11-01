#ifndef __HW1__RAY__
#define __HW1__RAY__

#include "Vector.h"

struct Ray{

    Ray(): origin(Point()), direction(Vec3f()) { }
    Ray(const Ray& r): origin(r.origin), direction(r.direction) { }
    Ray(const Point& origin, const Vec3f& direction): origin(origin), direction(direction) { }
    Point origin;
    Vec3f direction;

    Point calculate(float t) {
        return origin + direction * t;
    }

};

#endif