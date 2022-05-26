#pragma once

#ifndef FACE_H_INCLUDED
#define FACE_H_INCLUDED

#include "VectorMath.h"

typedef struct Face {
	Vec3 *p1, *p2, *p3;
	GLfloat Aot;
	Vec3 UnitNormal;
	GLfloat *colour;
}Face;

GLfloat faceArea(const Face *f);
Vec3 faceUnitNormal(const Face *f);

#endif // FACE_H_INCLUDED