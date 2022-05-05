#pragma once

#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <math.h>
#include "Face.h"
#include "OffFile.h"

typedef struct Body {
	GLfloat mass;
	Vec3 velocity;
	Vec3 acceleration;
	Vec3 position;
	Vec3 scale;
	Vec3 rotation;
	GLfloat rotAngle;
	GLfloat radius;
}Body;

typedef struct Object {
	OffModel off;
	Body body;
}Object;

static void getBody(Object* obj) { return obj->body; }
static void getOffModel(Object* obj) { return obj->off; }

void updateObject(Object* obj, float deltaTime);
void updatePrevObject(Object* obj);

Vec3 centerOfMass(OffModel* cModel);
GLfloat radiusOfBoundingSphere(OffModel* cModel);
void normalizeOffModel(OffModel* cModel);

void loadOffObject(char* filename, Object* obj);
void drawComplexObject(Object* obj);
void drawSphereObject(Object* obj);

#endif
