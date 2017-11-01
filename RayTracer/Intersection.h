#ifndef __HW1__INTERSECTION__
#define __HW1__INTERSECTION__

#include "Ray.h"
#include "Vector.h"

struct Shape;

struct Intersection {

  Intersection() : ray(), pSphere(nullptr), t(1.0e30f), surfaceNormal() {}
  Intersection(const Intersection &other)
      : ray(other.ray), t(other.t), pSphere(other.pSphere),
        surfaceNormal(other.surfaceNormal) {}
  Intersection(const Ray &ray)
      : ray(ray), t(1.0e30f), pSphere(nullptr), surfaceNormal() {}
  Ray ray;
  Shape *pSphere;
  float t;
  Vec3f surfaceNormal;

  Intersection &operator=(const Intersection &other) {
    ray = other.ray;
    surfaceNormal = other.surfaceNormal;
    t = other.t;
    pSphere = other.pSphere;
  }

  bool intersected() { return bool(pSphere); }

  Point hitPoint() { return ray.calculate(t); }
};

#endif
