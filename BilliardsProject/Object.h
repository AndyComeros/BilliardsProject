#pragma once

#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <math.h>
#include "Face.h"
#include "OffFile.h"
#include "Lighting.h"

/**
*	@brief Phyics body data for an object
*/
typedef struct Body {
		///Mass
	GLfloat mass;
		///Objects velocty
	Vec3 velocity;
		///Current acceleration
	Vec3 acceleration;
		///Position in worldspace
	Vec3 position;
		///Scale change on each axis
	Vec3 scale;
		///amount currently rotating along each axis
	Vec3 rotation;
		///total angle currently rotated
	GLfloat rotAngle;
		///radius for a sphere collider
	GLfloat radius;
		///if the object is currently moving and needs to be updated
	int  isMoving;
}Body;
/**
*	@brief Object represents an item that can be rendered. Contains a physics body for 
*	simulating interations with other objects. 
*/
typedef struct Object {
		///3D model data
	OffModel off;
		///Physics body data
	Body body;
		///Lighting material properties
	Material material;
		/// 0 is inactive (false), 1 is active (true)
	int isActive; 
}Object;

//whether to draw ball or other object
int ballMode;

static void getBody(Object* obj) { return obj->body; }
static void getOffModel(Object* obj) { return obj->off; }
	/**
	*	@brief Main physics update to change objects position based on current velocity
	*	also reduces overall velocity every frame to simulate friction/air resistance.
	*	@param obj - object currently being simulated
	*/
void updateObject(Object* obj, float deltaTime);
	/**
	*	@brief, calculates a 3D models center of mass
	*	@param cModel - model the center of mass is found for
	*	@return  Vec3  - coordinates of center of mass
	*/
Vec3 centerOfMass(OffModel* cModel);
	/**
	*	@brief calculates the radius of the smallest spehere that surrounds all vertecies of the 3D model
	*	@param cModel - 3D model the radius is found for
	*	@return GLfloat - radius of boundingSphere
	*/
GLfloat radiusOfBoundingSphere(OffModel* cModel);
	/**
	*	@brief puts the center of the 3D model at 0,0,0 and scales its size to have a bounding
	*	sphere radius of 1.
	*	@param cModel - 3D model being normalized
	*	@return void
	*/
void normalizeOffModel(OffModel* cModel);
	/**
	*	@brief loads a 3D model into the OFF data of an object
	*	@return void
	*/
void loadOffObject(char* filename, Object* obj);
	/**
	*	@brief renders an Object using its 3D model data
	*	@param obj -  the object being rendered
	*	@return void
	*/
void drawComplexObject(Object* obj);
	/**
	*	@brief draws a circlular shadow along the x-z plane, useful for simulating
	*	shadows underneath speheres
	*	@return void
	*/
void drawSphereShadow();
	/**
	*	@brief Renders an object as a sphere rather than using its 3D model data
	*	@param obj - object being rendered
	*	@return void
	*/
void drawSphereObject(Object* obj);

#endif
