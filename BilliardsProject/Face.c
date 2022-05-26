#include "Face.h"

GLfloat faceArea(const Face* f)
{
	Vec3 result = cross(minus(*f->p2, *f->p1), minus(*f->p3, *f->p1));
	return length(result) / 2;
}

Vec3 faceUnitNormal(const Face* f)
{
	return normalize(cross(minus(*f->p1, *f->p2), minus(*f->p1, *f->p3)));
}
