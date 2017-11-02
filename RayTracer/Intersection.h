#ifndef __HW__INTERSECTION__
#define __HW__INTERSECTION__

#include "Ray.h"
#include "Vector.h"

struct Shape;

struct Intersection
{
    Intersection() : ray(), pSphere(nullptr), t(1000000.0f), surfaceNormal(){}
    Intersection(const Intersection &other)
        : ray(other.ray), t(other.t), pSphere(other.pSphere),
        surfaceNormal(other.surfaceNormal){}
    Intersection(const Ray &ray)
        : ray(ray), t(1000000.0f), pSphere(nullptr), surfaceNormal(){}

    Ray ray;
    Shape *pSphere;
    float t;
    Vec3f surfaceNormal;

    Intersection &operator=(const Intersection &other)
    {
        ray = other.ray;
        surfaceNormal = other.surfaceNormal;
        t = other.t;
        pSphere = other.pSphere;
        return *this;
    }

    bool intersected() { return bool(pSphere); }

    Point hitPoint() { return ray.calculate(t); }
};

#endif