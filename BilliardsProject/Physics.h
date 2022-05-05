#pragma once

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "Object.h"
#include "Face.h"

void resolveCollisionObjPlane(Object* obj, Face* f);
Vec3 collisionResolution(Vec3* vec, Vec3* norm);

void applyForce(Object* obj, Vec3 f);

GLfloat DistanceBetweenObjPlane(Object* obj, Face* f); // returns the distance

Vec3 calcForce(Object* obj);

#endif // !PHYSICS_H_INCLUDED
