#pragma once
#include "Vector.h"

typedef vect3D point3D;

GLfloat triangleArea(point3D p1, point3D p2, point3D p3);
vect3D triangleNormal(point3D p1, point3D p2, point3D p3);
vect3D triangleUnitNormal(point3D p1, point3D p2, point3D p3);