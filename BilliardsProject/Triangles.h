#pragma once

#ifndef TRIANGLES_H_INCLUDED
#define TRIANGLES_H_INCLUDED

#include "Vector.h"

typedef struct{
	Vec3 p1, p2, p3;
	Vec3 unitNormal;
	GLfloat AoT;
}Triangle;

GLfloat triangleArea(Vec3 p1, Vec3 p2, Vec3 p3);
Vec3 triangleNormal(Vec3 p1, Vec3 p2, Vec3 p3);
Vec3 triangleUnitNormal(Vec3 p1, Vec3 p2, Vec3 p3);

#endif // TRIANGLES_H_INCLUDED