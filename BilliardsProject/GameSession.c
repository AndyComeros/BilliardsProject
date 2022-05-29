#include "GameSession.h"
#include "GameInput.h"

#define STARTING_HEIGHT 10
#define BALLCOUNT 7


static Object ball = {
	{NULL, // faces ptr
	NULL, // vertex ptr
	0, 0, 0}, // number of vertex, faces, edges

	{1, // mass
	{0, 0, 0}, // velocity
	{0, 0, 0}, // acceleration
	{0, STARTING_HEIGHT, 0}, // position;
	{1, 1, 1}, // scale;
	{0, 1, 0}, // rotation;
	0, // rotation angle
	1, // radius
	0 // isMoving
	},

	1 // isActive (true)
};

//static const Vec3 gravity = { 0.0, -GRAVITY, 0.0 };

static Vec3 planeP1 = { 2, 0, 2 }, planeP2 = { 1, 0, 1 }, planeP3 = { -1, 0, -1 };

static Face plane = {
	&planeP1,
	&planeP2,
	&planeP3,
	{0},
	{0, 1, 0}
};

Object balls[BALLCOUNT];

void initGameSession()
{
	gameStartingSetup();
}

void gameStartingSetup()
{
	for (int i = 0; i < BALLCOUNT; i++)
	{
		balls[i] = ball;
		testObjBody(&balls[i], i);
	}

	initGameInput(&balls[0]);
}

void animateGameObjects(float deltaTime)
{
	for (int i = 0; i < BALLCOUNT; i++)
	{
		//applyForce(&balls[i], gravity); // gravity
		//rotateObjects(&balls[i]);
		if (DistanceBetweenObjPlane(&balls[i], &plane) < 1.0f)
		{
			resolveCollisionObjPlane(&balls[i], &plane);
		}
		tableAABB(&balls[i].body);
		updateObject(&balls[i], deltaTime);
	}

	//simulate elastic collision between balls
	int activeCount = 0;
	for (size_t i = 0; i < BALLCOUNT; i++)
	{
		if (balls[i].body.isMoving != 0) {
			activeCount++;
			isHittable = 0;
		}

		for (size_t j = i + 1; j < BALLCOUNT; j++)
		{
			physicSphereCollide(&balls[i].body, &balls[j].body);
		}
		//rotate balls. not final, not sure if correct but looks convining
		balls[i].body.rotation = normalize(balls[i].body.velocity);
		balls[i].body.rotAngle += length(balls[i].body.velocity);
	}

	if (activeCount == 0 && activeMenu == 3) {
		isHittable = 1;
	}
}

void testObjBody(Object* obj, int index) {

	obj->body.radius = 2;
	obj->body.mass = 3;
	obj->body.isMoving = 0;
	switch (index) {
	case 0:
		obj->body.position.x = 20;
		obj->body.position.z = 0;
		//obj->body.mass = 30;
		break;
	case 1:
		obj->body.position.x = 0;
		obj->body.position.z = 0;
		break;
	case 2:
		obj->body.position.x = -5;
		obj->body.position.z = 2.2;
		break;
	case 3:
		obj->body.position.x = -5;
		obj->body.position.z = -2.2;
		break;
	case 4:
		obj->body.position.x = -10;
		obj->body.position.z = 0;
		break;
	case 5:
		obj->body.position.x = -10;
		obj->body.position.z = 4.0;
		break;
	case 6:
		obj->body.position.x = -10;
		obj->body.position.z = -4.0;
		break;

	}

	obj->body.position.y = 3;
	//obj->body.rotAngle = rand() % 360;
	obj->body.scale.x = 2;
	obj->body.scale.y = 2;
	obj->body.scale.z = 2;
	obj->body.mass *= 2;
	obj->isActive = 1;

}

void randObjBody(Object* obj)
{
	obj->body.position.z = rand() % 20 - 10;
	obj->body.position.x = rand() % 10 - 5;
	obj->body.position.y = rand() % 30 + 15;
	obj->body.rotAngle = rand() % 360;
	GLfloat r = (rand() % 3);
	if (r == 0) r = 1;
	obj->body.scale.x = r;
	obj->body.scale.y = r;
	obj->body.scale.z = r;
	obj->body.mass *= r;
}

void rotateObjects(Object* obj)
{
	if (obj->body.rotAngle >= 360)
	{
		obj->body.rotAngle = 0;
	}
	else
	{
		obj->body.rotAngle += 1;
	}
}

void drawBallObjects()
{
	for (int i = 0; i < BALLCOUNT; i++)
	{
		if (&balls[i].isActive != 0) // true
		{
			drawSphereObject(&balls[i]);
		}
	}
}
