#include "Physics.h"
#include <stdio.h>

#define BOUNCEDECAY 0.9

void resolveCollisionObjPlane(Object* obj, Face* f)
{
	if (obj->body.velocity.x != 0) obj->body.velocity.x *= BOUNCEDECAY;
	if (obj->body.velocity.y < 0) obj->body.velocity.y *= -1 * BOUNCEDECAY; // bouncing
	if (obj->body.velocity.z != 0) obj->body.velocity.z *= BOUNCEDECAY;
}

Vec3 collisionResolution(Vec3* vec, Vec3* norm)
{
	GLfloat dotprod = dot(*vec, *norm);
	Vec3 result = minus((multiply(*norm, 2 * dotprod)), *vec);
	return multiply(result, BOUNCEDECAY);
}

void applyForce(Object* obj, Vec3 f)
{
	obj->body.acceleration.x += f.x / obj->body.mass;
	obj->body.acceleration.y += f.y / obj->body.mass;
	obj->body.acceleration.z += f.z / obj->body.mass;
}

GLfloat DistanceBetweenObjPlane(Object* obj, Face* f)
{
	return (-dot(minus(obj->body.position, *f->p1), f->UnitNormal)) - obj->body.radius;
}

Vec3 calcForce(Object* obj)
{
	return multiply(obj->body.acceleration, obj->body.mass);
}
