#ifndef __HW1__VECTOR__
#define __HW1__VECTOR__

#include <cmath>

struct Vec3f
{
    Vec3f():x(0.0f), y(0.0f), z(0.0f) { }
    Vec3f(const Vec3f& v):x(v.x), y(v.y), z(v.z) { }
    Vec3f(float x, float y, float z): x(x),y(y),z(z) { }
    
    float x, y, z;

    float len2() { return x*x + y*y + z*z; }
    float len() { return std::sqrt(len2()); }
    float normalize() {
        float length = len();
        (*this)/=length;
        return length;
    }
    Vec3f normalized(){
        Vec3f v(*this);
        v.normalize();
        return v;
    }

    Vec3f& operator= (const Vec3f& other)
    {
        this->x=other.x;
        this->y=other.y;
        this->z=other.z;
        return *this;
    }
    Vec3f& operator+= (const Vec3f& other)
    {
        this->x+other.x;
        this->y+other.y;
        this->z+other.z;
        return *this;
    }
    Vec3f& operator-= (const Vec3f& other)
    {
        this->x-other.x;
        this->y-other.y;
        this->z-other.z;
        return *this;
    }
    Vec3f& operator*= (float& other)
    {
        this->x*other;
        this->y*other;
        this->z*other;
        return *this;
    }
    Vec3f& operator/= (float other)
    {
        this->x/other;
        this->y/other;
        this->z/other;
        return *this;
    }
    Vec3f operator- ()
    {
        return Vec3f(-x, -y, -z);
    }

};

inline Vec3f operator+(const Vec3f& a, const Vec3f& b)
{
    return Vec3f(a.x+b.x, a.y+b.y, a.z+b.z);
}
inline Vec3f operator-(const Vec3f& a, const Vec3f& b)
{
    return Vec3f(a.x-b.x, a.y-b.y, a.z-b.z);
}
inline Vec3f operator*(const Vec3f& a, float b)
{
    return Vec3f(a.x*b, a.y*b, a.z*b);
}

inline Vec3f operator/(const Vec3f& a, float b)
{
    return Vec3f(a.x/b, a.y/b, a.z/b);
}

inline float dot(const Vec3f& a, const Vec3f& b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
inline Vec3f cross(const Vec3f& a, const Vec3f& b)
{
    return Vec3f(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

typedef Vec3f Point;

struct Vec3i
{
    int x, y, z;
};

struct Vec4f
{
    float x, y, z, w;
};

#endif