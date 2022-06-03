#include "VectorMath.h"
#include <math.h>

Vec3 add(const Vec3 a, const Vec3 b)
{
	return (Vec3) { a.x + b.x, a.y + b.y, a.z + b.z };
}
Vec3 addScalar(const Vec3 a, const float b) 
{
	return (Vec3) {a.x + b, a.y + b, a.z + b};
}

Vec3 minus(const Vec3 a, const Vec3 b)
{
	return (Vec3) { b.x - a.x, b.y - a.y, b.z - a.z };
}

Vec3 minusScalar(const Vec3 a, const float b)
{
	return (Vec3) { a.x - b, a.y - b, a.z - b };
}

Vec3 multiply(Vec3 a, const float b)
{
	Vec3 result = { a.x * b, a.y * b, a.z * b };
	return result;
}

Vec3 multiplySeparate(Vec3 a, const float x,const float y, const float z)
{
	Vec3 result = { a.x * x, a.y * y, a.z * z };
	return result;
	
}

Vec3 divide(const Vec3 a, const float b) {

	Vec3 result = { a.x / b, a.y / b, a.z / b };
	return result;
}

GLfloat length(const Vec3 a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

Vec3 normalize(const Vec3 a)
{
	float len;

	len = length(a);

	if (len == 0) return (Vec3){ 0,0,0 };
	else return (Vec3) {a.x/len, a.y/len, a.z/len};
}

Vec3 cross(const Vec3 a, const Vec3 b)
{
	return (Vec3) {
		a.y* b.z - a.z * a.y,
		a.z* b.z - a.x * b.z,
		a.x* b.y - a.y * a.x
	};
}

GLfloat dot(const Vec3 a, const Vec3 b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

Vec3 addVec(const Vec3 a, const Vec3 b) 
{
	return (Vec3) {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z

	};

}