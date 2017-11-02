#ifndef __HW__SHAPE__
#define __HW__SHAPE__

#include <iostream>
#include <vector>
#include <math.h>
#include "Vector.h"
#include "Intersection.h"

struct Face
{
    int v0_id;
    int v1_id;
    int v2_id;
};

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

struct Mesh
{
    int material_id;
    std::vector<Face> faces;
};

struct Triangle: public Shape
{
    int material_id;
    Face indices;

    float determinant_2(float a, float b, float c, float d)
    {
        return a*d - b*c;
    }
    
    float determinant_3(Vec3f row1, Vec3f row2, Vec3f row3)
    {
        return row1.x * determinant_2(row2.y, row2.z, row3.y, row3.z) + row1.y * determinant_2(row2.x, row2.z, row3.x, row3.z)
            + row1.z * determinant_2(row2.x, row2.y, row3.x, row3.y);
    }

    bool intersect(Intersection &i, const std::vector<Vec3f> &vertex_data)
    {
        Ray ray = i.ray;
        Vec3f direction = i.ray.direction;

        Point a = vertex_data[indices.v0_id];
        Point b = vertex_data[indices.v1_id];
        Point c = vertex_data[indices.v2_id];

        //float A = determinant_3(a_b, a_c, direction);

        float A = determinant_3(Vec3f(a.x - b.x, a.x - c.x, direction.x),
        Vec3f(a.y - b.y, a.y - c.y, direction.y),
        Vec3f(a.z - b.z, a.z - c.z, direction.z));

        std::cout << a.x << " " << a.y << " " << a.z << std::endl;

        float beta = determinant_3(Vec3f(a.x - ray.origin.x, a.x - c.x, direction.x),
                                    Vec3f(a.y - ray.origin.y, a.y - c.y, direction.y),
                                    Vec3f(a.z - ray.origin.z, a.z - c.z, direction.z)) / A;

        //if(beta >= 0)
        //std::cout << A << std::endl;

        float gamma = determinant_3(Vec3f(a.x - b.x, a.x - ray.origin.x, direction.x),
                                    Vec3f(a.y - b.y, a.y - ray.origin.y, direction.y),
                                    Vec3f(a.z - b.z, a.z - ray.origin.z, direction.z)) / A;


        float t = determinant_3(Vec3f(a.x - b.x, a.x - c.x, a.x - ray.origin.x),
                                    Vec3f(a.y - b.y, a.y - c.y, a.y - ray.origin.y),
                                    Vec3f(a.z - b.z, a.z - c.z, a.z - ray.origin.z)) / A;

        //std::cout << A << " " << beta << " " << gamma << " " << t << std::endl;

        if(t > 0 && 0 <= beta && 0 <= gamma && beta + gamma <= 1)
        {
            i.t = t;
        }
        else
        {
            return false;
        }
        return true;
    }
};

#endif