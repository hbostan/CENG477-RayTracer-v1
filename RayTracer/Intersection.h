#ifndef __HW__INTERSECTION__
#define __HW__INTERSECTION__

#include "Ray.h"
#include "Vector.h"

struct Shape;

struct Intersection
{
    Intersection() : ray(), pSphere(nullptr), t(INFINITY), surfaceNormal(), material_id(-1){}
    Intersection(const Intersection &other)
        : ray(other.ray), t(other.t), pSphere(other.pSphere),
        surfaceNormal(other.surfaceNormal), material_id(other.material_id){}
    Intersection(const Ray &ray)
        : ray(ray), t(INFINITY), pSphere(nullptr), surfaceNormal(), material_id(-1){}

    Ray ray;
    Shape *pSphere;
    float t;
    Vec3f surfaceNormal;
    int material_id;

    Intersection &operator=(const Intersection &other)
    {
        ray = other.ray;
        surfaceNormal = other.surfaceNormal;
        t = other.t;
        pSphere = other.pSphere;
        return *this;
    }
    
    bool intersected() { return bool(t < INFINITY); }

    Point hitPoint() { return ray.calculate(t); }
};

#endif