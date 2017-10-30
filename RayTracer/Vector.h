


class Vec3f {
public:
	float x, y, z;

	Vec3f();
	Vec3f(const Vec3f& other) :x(other.x), y(other.y), z(other.z) {};
	Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};
	Vec3f(float d) :x(d), y(d), z(d) {};

	float length();
	float sqrLength();

	float normalize();
	Vec3f normalized();


	Vec3f& operator =(const Vec3f& v);
	Vec3f& operator +=(const Vec3f& v);
	Vec3f& operator -=(const Vec3f& v);
	Vec3f& operator *=(const Vec3f& v);
	Vec3f& operator /=(const Vec3f& v);
	Vec3f operator -();

	float dot(Vec3f v);
	Vec3f cross(Vec3f v);
};

typedef Vec3f Point;

class Vec3i {
public:
	int x, y, z;

	Vec3i();
	Vec3i(const Vec3i& other) :x(other.x), y(other.y), z(other.z) {};
	Vec3i(int x, int y, int z) : x(x), y(y), z(z) {};
	Vec3i(int d) :x(d), y(d), z(d) {};

	float length();
	int sqrLength();

	/*float normalize();
	Vec3i normalized();*/


	Vec3i& operator =(const Vec3i& v);
	Vec3i& operator +=(const Vec3i& v);
	Vec3i& operator -=(const Vec3i& v);
	Vec3i& operator *=(const Vec3i& v);
	Vec3i& operator /=(const Vec3i& v);
	Vec3i operator -();

	int dot(Vec3i v);
	Vec3i cross(Vec3i v);
};

class Vec4f {
	float x, y, z, w;
};