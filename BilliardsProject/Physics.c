#include "Physics.h"
#include <stdio.h>

#define BOUNCEDECAY 0.99
#define FLOORWIDTH 50.f
#define FLOORLENGTH 75.f
#define WALLHEIGHT 10.f
#define HALFSIZEOFHOLE 5.f
#define WALLOFFSET 50.f


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
			GLfloat b1MassRatio = (ball2->mass)/tMass;
			GLfloat b2MassRatio = (ball1->mass)/tMass;

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

void tableAABB(Body* ball)
{
	GLfloat rad = ball->radius*1.2f; // minus or plus 1 for radius of ball, little extra to make is seem more accurate and not phase through walls
	GLfloat posX = ball->position.x, posZ = ball->position.z; // local variables
	GLfloat floorLen = FLOORLENGTH - rad;
	GLfloat floorWid = FLOORWIDTH - rad;
	GLfloat holeSize = HALFSIZEOFHOLE - rad;

	// if its within bounds, just return. saves computation
	if (posX < floorLen && posX > -floorLen && posZ < floorWid && posZ > -floorWid)
	{
		return;
	}

	// back wall
	Vec3 v_backwall = { 1.f, 0.f, 0.f }, // unit normal from back wall
		v_frontwall = { -1.f, 0.f, 0.f }, // unit mornal for front wall
		v_leftwall = { 0.f, 0.f, -1.f }, // unit normal for left wall
		v_rightwall = { 0.f, 0.f, 1.f }; // unit normal for right wall

	if (posX < -floorLen  // further than back wall
		&& posZ > (-floorWid + holeSize) // not in back left hole
		&& posZ < (floorWid - holeSize) // not in back right hole
		)
	{
		//printf("BOUNCE BACK WALL\n");
		ball->velocity = collisionResolution(&ball->velocity, &v_backwall); // collided with back wall, reflect ball
	}

	// front wall
	if (posX > floorLen  // further than front wall
		&& posZ > (-floorWid + holeSize) // not in front left hole
		&& posZ < (floorWid - holeSize) // not in front right hole
		)
	{
		//printf("BOUNCE FRONT WALL\n");
		ball->velocity = collisionResolution(&ball->velocity, &v_frontwall); // collided with front wall, reflect ball
	}

	// top left wall and bottom left wall
	if (
		// top left wall
		posZ > floorWid // further than left wall
		&& posX > -floorLen // not in top left hole
		&& posX < -holeSize // not in middle hole
		|| // or in bottom half
		posZ > floorWid // further than left wall
		&& posX < floorLen // not in middle hole
		&& posX > holeSize // not in bottom left hole
		) 
	{
		//printf("BOUNCE LEFT WALL\n");
		ball->velocity = collisionResolution(&ball->velocity, &v_leftwall);
	}

	// top right wall and bottom right wall
	if (
		// top right wall
		posZ < -floorWid // further than right wall
		&& posX > -floorLen // not in top right hole
		&& posX < -holeSize // not in middle hole
		|| // or in bottom half
		posZ < -floorWid // further than right wall
		&& posX < floorLen // not in middle hole
		&& posX > holeSize // not in bottom right hole
		)
	{
		//printf("BOUNCE LEFT WALL\n");
		ball->velocity = collisionResolution(&ball->velocity, &v_rightwall);
	}
}

int holeAABB(Body* ball)
{
	GLfloat rad = ball->radius * 1.5; // minus or plus 1 for radius of ball, little extra to make is seem more accurate and not phase through walls
	GLfloat posX = ball->position.x, posZ = ball->position.z; // local variables
	GLfloat holeSize = HALFSIZEOFHOLE - rad;
	GLfloat floorLen = FLOORLENGTH - holeSize;
	GLfloat floorWid = FLOORWIDTH - holeSize;

	// in mid left hole
	if (posX < holeSize && posX > -holeSize && posZ < -floorWid) return 1;
	// in mid right hole
	if (posX < holeSize && posX > -holeSize && posZ > floorWid) return 1;

	// if its within bounds, just return. saves computation
	if (posX < floorLen && posX > -floorLen && posZ < floorWid && posZ > -floorWid)
	{
		 return 0; // return false
	}


	// in top left hole
	if (posX < floorLen && posZ > floorWid) return 1;
	// in top right hole
	if (posX < floorLen && posZ < -floorWid) return 1;
	// in bottom left hole
	if (posX > -floorLen && posZ > floorWid) return 1;
	// in bottom right hole
	if (posX > -floorLen && posZ < -floorWid) return 1;

	//printf("After Check\n");

	//// if its outside bounds, just return true
	//if (posX > FLOORLENGTH + WALLOFFSET
	//	|| posX < -(FLOORLENGTH + WALLOFFSET)
	//	|| posZ > FLOORWIDTH + WALLOFFSET
	//	|| posZ < -(FLOORWIDTH + WALLOFFSET))
	//{
	//	return 1; // return true
	//}

	return 0; // default return false
}
