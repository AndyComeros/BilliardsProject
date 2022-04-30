#pragma once

#ifndef TRIANGLES_H_INCLUDED
#define TRIANGLES_H_INCLUDED

#include "Vector.h"

typedef Vec3 point3D;

GLfloat triangleArea(point3D p1, point3D p2, point3D p3);
Vec3 triangleNormal(point3D p1, point3D p2, point3D p3);
Vec3 triangleUnitNormal(point3D p1, point3D p2, point3D p3);

#endif // TRIANGLES_H_INCLUDED