#ifndef __HW__SHAPE__
#define __HW__SHAPE__

#include <iostream>
#include <vector>
#include <math.h>
#include "Vector.h"
#include "Intersection.h"

struct Shape
{
    virtual bool intersect(Intersection& i, const std::vector<Vec3f> &vertex_data) = 0;
};

struct Sphere: public Shape
{
    int material_id;
    int center_vertex_id;
    float radius;

    bool intersect(Intersection &i, const std::vector<Vec3f> &vertex_data)
    {
        Point center = vertex_data[center_vertex_id];

        float root1, root2;
        Ray ray = i.ray;

        Vec3f direction = ray.direction;
        Vec3f distance_vector = ray.origin - center;
                    
        float A = direction.dot(direction);
        float B = direction.dot(distance_vector) * 2;
        float C = distance_vector.dot(distance_vector) - radius * radius;
        
        float discriminant = B * B - 4 * A * C;
        if(discriminant < 0) return false;
        else
        {
            discriminant = sqrt(discriminant);
            root1 = (-B + discriminant)/(2*A);
            root2 = (-B - discriminant)/(2*A); 
        }
            
        float small = root1 < root2 ? root1 : root2;
        float big = root1 > root2 ? root1 : root2;

        if(small < 0)
        {
            if(big < 0) return false;
            i.t = big;
        }
        else
        {
            i.t = small;
        }

        i.surfaceNormal = ray.calculate(i.t).normalized();
        i.pSphere = this;

        return true;
    }
};

#endif