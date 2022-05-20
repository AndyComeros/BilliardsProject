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

void physicSphereCollide(Body *ball1, Body *ball2) 
{
	//multiple passes make collisions more accurate(for multiple collisions in one frame), reduce number for perfomance
	for (size_t x = 0; x < 5; x++)
	{

		//expensive square root... anyother way?- might not be relavant when so little objects are on screen
		GLfloat distance = length(minus(ball1->position, ball2->position));

		//if balls collide
		if (abs(distance) < (ball1->radius + ball2->radius))
		{
			//stops balls from entering each other
			GLfloat intersection = ((distance - (ball1->radius + ball2->radius)) / 2);//get length ofintersection

			ball1->position.x -= intersection * (ball1->position.x - ball2->position.x);
			ball1->position.z -= intersection * (ball1->position.z - ball2->position.z);

			ball2->position.x += intersection * (ball2->position.x - ball2->position.x);
			ball2->position.z += intersection * (ball2->position.z - ball2->position.z);

			//collision formula from: https://en.wikipedia.org/wiki/Elastic_collision
			//can be extrapolated to 3D but our game is technically a 2D sim
			Vec3 b1Vel = ball1->velocity;
			Vec3 b2Vel = ball2->velocity;
			Vec3 b1Pos = ball1->position;
			Vec3 b2Pos = ball2->position;
			
			
			GLfloat tMass = (ball1->mass + ball2->mass);
			GLfloat b1MassRatio = (2 * ball2->mass)/tMass;
			GLfloat b2MassRatio = (2 * ball1->mass)/tMass;

			//dot products
			GLfloat dotProd1 = dot(minus(b1Vel,b2Vel),minus(b1Pos,b2Pos)) / (distance * distance);
			GLfloat dotProd2 = dot(minus(b2Vel,b1Vel),minus(b2Pos,b1Pos)) / (distance * distance);

			ball1->velocity.x = b1Vel.x - b1MassRatio * dotProd1 * (b1Pos.x - b2Pos.x);
			ball2->velocity.x = b2Vel.x - b2MassRatio * dotProd2 * (b2Pos.x - b1Pos.x);

			ball1->velocity.z = b1Vel.z - b1MassRatio * dotProd1 * (b1Pos.z - b2Pos.z);
			ball2->velocity.z = b2Vel.z - b2MassRatio * dotProd2 * (b2Pos.z - b1Pos.z);

			//ball1->velocity.y= b1Vel.y - b1MassRatio * dotProd1 * (b1Pos.y - b2Pos.y);
			//ball2->velocity.y = b2Vel.y - b2MassRatio * dotProd2 * (b2Pos.y - b1Pos.y);
		}
	}
}