#ifndef _HW_CAMERA_
#define _HW_CAMERA_

#include "Vector.h"
#include "Ray.h"
#include <string>
#include <iostream>

struct Camera
{
    Camera() :initialized(false) {}

    bool initialized;
    Point position;
    Vec3f gaze;
    Vec3f up;
    Vec4f near_plane;
    float near_distance;
    int image_width, image_height;
    std::string image_name;

    Vec3f right_vector;
    float left;
    float right;
    float bottom;
    float top;
    float horizontal_step;
    float vertical_step;
    Point m, q;

    void initCamera()
    {
        right_vector = up.cross(-gaze);
        
        left = near_plane.x;
        right = near_plane.y;
        bottom = near_plane.z;
        top = near_plane.w;
        
        m = position + gaze * near_distance;
        q = m + (right_vector * left + up * top);
        
        horizontal_step = (right - left)/image_width;
        vertical_step = (top - bottom)/image_height;
    }

    Ray makeRay(int x, int y)
    {
        float u = left + horizontal_step * (x+0.5);
        float v = top - vertical_step * (y+0.5);

        Point s = q + up * u + right_vector * v;

        Vec3f d = s - position;
        d.normalize();

        

        return Ray(position, d);
    }
};

#endif