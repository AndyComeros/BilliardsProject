#pragma once

#ifndef VECTORMATH_H_INCLUDED
#define VECTORMATH_H_INCLUDED

#include <GL\freeglut.h>

/**
*	@brief Represents a 3 dimensional vector
*/
typedef struct Vec3 {
	GLfloat x, y, z;
}Vec3;
	/**
	*	@brief adds 2 vectors together
	*	@param a first vector
	*	@param b second vector
	*	@return Vec3 - resulting vector
	*/
Vec3 add(const Vec3 a, const Vec3 b);
	/**
	*	@brief	adds each element in a vector with a scalar value
	*	@param a - vector the scalar is being added to
	*	@param b - scalar value being added to vector
	*	@return Vec3 - resulting vector
	*/
Vec3 addScalar(const Vec3 a, const float b);
	/**
	*	@brief subtracts 1 from another together
	*	@param a - vector having second vector subtracted from
	*	@param b - vector being subtracted from a
	*	@return Vec3 - resulting vector
	*/
Vec3 minus(const Vec3 a, const Vec3 b);
	/**
	*	@brief subtracts each element of a vector with a scalar value
	*	@param a  - vector being subtracted from
	*	@param b - scalar value being subtracted
	*	@return Vec3 - resulting vector
	*/
Vec3 minusScalar(const Vec3 a, const float b);
	/**
	*	@brief Multiplies a vector with a scaler value
	*	@param a - vector being multiplied
	*	@param b - scalar value the vector is multiplied by
	*	@return Vec3 - resulting vector
	*/
Vec3 multiply(const Vec3 a, const float b);
	/**
	*	@brief multiplies each value in a vecotor by different scalar values
	*	@param a - vector being multiplied
	*	@param x - scalar value vectors x is multiplied by
	*	@param y - scalar value vectors y is multiplied by
	*	@param z - scalar value vectors z is multiplied by
	*	@return Vec3 - resulting vector
	*/
Vec3 multiplySeparate(Vec3 a, const float x, const float y, const float z);
	/**
	*	@brief Divides a vector by a scalar value
	*	@param a - vector being divided
	*	@param b - scalar value vector is divided by
	*	@return Vec3 - resulting vector
	*/
Vec3 divide(const Vec3 a, const float b);
	/**
	*	@brief Calculates the magnitude of a vector
	*	@param a - Vector the magnitude is calculated for
	*	@return Vec3 - resulting vector
	*/
GLfloat length(const Vec3 a);
	/**
	*	@brief Calculates the normalized version of a vector
	*	@param a - vector being normalized
	*	@return Vec3 - resulting vector
	*/
Vec3 normalize(const Vec3 a);
	/**
	*	@brief Calculates the cross product of 2 vectors
	*	@param a - first vector
	*	@param b - second vector
	*	@return Vec3 - resulting vector
	*/
Vec3 cross(const Vec3 a, const Vec3 b);
	/**
	*	@brief Calculates the dot product of 2 vectors
	*	@param a - first vector
	*	@param b - second vector
	*	@return Vec3 - resulting vector
	*/
GLfloat dot(const Vec3 a, const Vec3 b);
	/**
	*	@brief adds 2 vectors together
	*	@param a - first vector
	*	@param b - second vector
	*	@return Vec3 - resulting vector
	*/
Vec3 addVec(const Vec3 a, const Vec3 b);

#endif // VECTORMATH_H_INCLUDED