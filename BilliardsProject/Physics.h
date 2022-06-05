#pragma once

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "Object.h"
#include "Face.h"
//plane collision
	/**
	*	@brief Simulates an object colliding with a surface.
	*	@param obj - object colliding with a plane
	*	@param f - face that object is colliding with, its normal will be used in the resolution
	*	@return void
	*/
void resolveCollisionObjPlane(Object* obj, Face* f);
	/**
	*	@brief Generic collision resolution. returns a changed velocity based on an initial velocity
	*	and a normal it is reflected against.
	*	@param vec - velocity
	*	@param norm - normal vector
	*	@return Vec3 - velocity vector after collision
	*/
Vec3 collisionResolution(Vec3* vec, Vec3* norm);
	/**
	*	@brief Applies a force vector to an object. the resulting velocity of the object
	*	is influenced by its mass, velocity, and current acceleration.
	*	@param obj - object adding force to
	*	@param	f - force vector being applied
	*/
void applyForce(Object* obj, Vec3 f);
	/**
	*	@brief Calculates the distance between an object and a plane
	*	@param obj - objects distance being calculated
	*	@param f - face on the plane being compared against
	*	@return GLfloat - distance between object and plane
	*/
GLfloat DistanceBetweenObjPlane(Object* obj, Face* f); // returns the distance
	/**
	*	@brief Calculates the current force of an object
	*	@param obj - object the force is calculated for
	*	@return Vec3 - force vector of the object
	*/
Vec3 calcForce(Object* obj);
//checks if 2 spheres are colliding, simulates a collision between the 2.
	/**
	*	@brief simulates an elastic collision between to object physics bodies as if they where both spheres.
	*	both physics bodies velocities are modified to represent the collision.
	*	@param ball1 - first ball in collision
	*	@param ball2 - second ball in collision
	*	@return void
	*/
void physicSphereCollide(Body *ball1, Body *ball2);
	/**
	*	@brief simulates a collison between a sphere and a pooltable.
	*	@param ball - ball being simulated
	*	@return void
	*/
void tableAABB(Body* ball);
/**
*	@brief checks if a ball has sunk into a pooltables holes
*	@param ball - ball being checked
*	@return int - if ball has been sunk or not 1 = true, 0 = false
*/
int holeAABB(Body* ball);

#endif // !PHYSICS_H_INCLUDED
