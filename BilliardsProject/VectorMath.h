#pragma once

#ifndef VECTORMATH_H_INCLUDED
#define VECTORMATH_H_INCLUDED

#include <GL\freeglut.h>

typedef struct Vec3 {
	GLfloat x, y, z;
}Vec3;

Vec3 add(const Vec3 a, const Vec3 b);
Vec3 addScalar(const Vec3 a, const float b);
Vec3 minus(const Vec3 a, const Vec3 b);
Vec3 minusScalar(const Vec3 a, const float b);
Vec3 multiply(const Vec3 a, const float b);
Vec3 multiplySeparate(Vec3 a, const float x, const float y, const float z);
Vec3 divide(const Vec3 a, const float b);

GLfloat length(const Vec3 a);
Vec3 normalize(const Vec3 a);

Vec3 cross(const Vec3 a, const Vec3 b);
GLfloat dot(const Vec3 a, const Vec3 b);

Vec3 addVec(const Vec3 a, const Vec3 b);

#endif // VECTORMATH_H_INCLUDED