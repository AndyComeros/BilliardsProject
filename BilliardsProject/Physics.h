#pragma once

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "Object.h"
#include "Face.h"

//plane collision
void resolveCollisionObjPlane(Object* obj, Face* f);

Vec3 collisionResolution(Vec3* vec, Vec3* norm);

void applyForce(Object* obj, Vec3 f);

GLfloat DistanceBetweenObjPlane(Object* obj, Face* f); // returns the distance


Vec3 calcForce(Object* obj);

//checks if 2 spheres are colliding, simulates a collision between the 2.
void physicSphereCollide(Body *ball1, Body *ball2);
void tableAABB(Body* ball);

#endif // !PHYSICS_H_INCLUDED
