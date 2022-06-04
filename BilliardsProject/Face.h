#pragma once

#ifndef FACE_H_INCLUDED
#define FACE_H_INCLUDED

#include "VectorMath.h"
	/**
	*	@brief specifies all the information for a face on a 3d face. useful
	*	for normals for lighting and physics for the specified face.
	*/
typedef struct Face {
		///Points that make up this face
	Vec3 *p1, *p2, *p3;
		///stores the total area of this face
	GLfloat Aot;
		///Norm for this face
	Vec3 UnitNormal;
	GLfloat *colour;
}Face;
	/**
	*	@brief Calculates the total area of the triangle
	*	@param f - pointer to the face being used
	*	@return GLfloat area of the face
	*/
GLfloat faceArea(const Face *f);
	/**
	*	@brief calculates the face norm
	*	@param f - face being used
	*	@return Vec3 - unit normal of f
	*/
Vec3 faceUnitNormal(const Face *f);

#endif // FACE_H_INCLUDED