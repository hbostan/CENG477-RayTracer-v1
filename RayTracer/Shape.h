#ifndef __HW1__SHAPE__
#define __HW1__SHAPE__

#include "Vector.h"
#include "Intersection.h"

struct Shape 
{
  virtual bool intersect(Intersection& i) =0 ;  
};

struct Sphere: public Shape
{
    int material_id;
    int center_vertex_id;
    float radius;
    Point center;

    bool intersect(Intersection &i){
        Ray translatedRay = i.ray;
        translatedRay.origin -= center;
    
        // Simplifies to the quadratic formula
        // a = 1
        float b = 2 * dot(translatedRay.origin, translatedRay.direction);
        float c = translatedRay.origin.len2() - (radius*radius);
    
        float discriminant = b*b - 4.0f * c;
        if (discriminant < 0.0f)
            return false;
    
        discriminant = std::sqrt(discriminant);
    
        float t1 = (-b + discriminant) / 2;
        float t2 = (-b - discriminant) / 2;
    
        if (t2 < t1)
        {
            float tmp = t2;
            t2 = t1;
            t1 = tmp;
        }
    
        if (t1 < i.t && t1 > 1.0e-5)
        {
            i.t = t1;
        }
        else if (t2 < i.t && t2 > 1.0e-5)
        {
            i.t = t2;
        }
        else
        {
            return false;
        }
    
        i.surfaceNormal = translatedRay.calculate(i.t).normalized();
        i.pSphere = this;
        //i.pMaterial = pMaterial;
    
        return true;

    }
};
#endif