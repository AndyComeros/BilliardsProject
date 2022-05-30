#include "GameSession.h"
#include "GameInput.h"

#define STARTING_HEIGHT 10
#define BALLCOUNT 16


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

static int ballSunkCount = 0;

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

	ballSunkCount = 0;
}

void animateGameObjects(float deltaTime)
{
	if (ballSunkCount == 15)
	{
		printf("WIN");
		// win screen
		//create win menu and call switchUI func here
		return;
	}

	if (balls[0].isActive == 0) resetWhiteBall(); // reset game ball if it goes inactive

	int activeCount = 0; // counting the amount of moving balls

	for (int i = 0; i < BALLCOUNT; i++)
	{

		if (balls[i].isActive == 0) // continue to next ball iteration if ball is inactive
		{
			//printf("inactive ball %d\n", i);
			continue;
		}

		if (balls[i].body.isMoving != 0) 
		{
			activeCount++;
			isHittable = 0;
		}

		//printf("Active %d: %d\n", i, balls[i].isActive);

		tableAABB(&balls[i].body); // if ball hits table walls, collision resolution

		if (holeAABB(&balls[i].body) == 1) // if ball hits one of the holes
		{
			printf("ball in hole\n");
			ballSunkCount++;
			printf("SunkCount: %d\n", ballSunkCount);
			balls[i].isActive = 0;
			continue;
		}

		updateObject(&balls[i], deltaTime);

		//simulate elastic collision between balls
		for (size_t j = i; j < BALLCOUNT; j++)
		{
			if(j != i) physicSphereCollide(&balls[i].body, &balls[j].body);
		}

		//rotate balls. not final, not sure if correct but looks convining
		Vec3 normRot = normalize(balls[i].body.velocity);

		balls[i].body.rotation.x = normRot.x;
		balls[i].body.rotation.y = 0;// normRot.y;
		balls[i].body.rotation.z = -normRot.z;



		//balls[i].body.rotation = normalize(balls[i].body.velocity);

		balls[i].body.rotAngle -= length(balls[i].body.velocity)/2.45;
	}

	if (activeCount == 0 && activeMenu == 3) 
	{
		isHittable = 1;
	}
}

float randCol() {
	return (float)rand() / RAND_MAX;
}
void testObjBody(Object* obj, int index) {

	obj->body.radius = 2;
	obj->body.mass = 3;
	obj->body.isMoving = 0;
	srand(88754535433 * index);
	
	float r = randCol();
	float g = randCol();
	float b = randCol();

	//r = r * 1.5;
	g = g * 0.7;
	//{0.1, 0.01, 0.1, 0.55}
	//scuff random colors
	Material ballMat =
	{
		{0.1, 0.1, 0.1, 0.55},
		{r,g,b, 1},
		{r,g,b, 0.55},
		100
	};

	Material whiteBall =
	{
		{1, 1, 1, 0.55},
		{1, 1, 1, 1},
		{1, 1, 1, 0.55},
		100
	};
	obj->material = ballMat;
	switch (index) {
	case 0:

		obj->material = whiteBall;
		obj->body.position.x = 40;
		obj->body.position.z = 0;
		//obj->body.mass = 30;
		break;
	case 1:
		obj->body.position.x = 0;
		obj->body.position.z = 0;
		break;
	case 2:
		obj->body.position.x = -5;
		obj->body.position.z = 2.5f;
		break;
	case 3:
		obj->body.position.x = -5;
		obj->body.position.z = -2.5f;
		break;
	case 4:
		obj->body.position.x = -10;
		obj->body.position.z = 0;
		break;
	case 5:
		obj->body.position.x = -10;
		obj->body.position.z = 5;
		break;
	case 6:
		obj->body.position.x = -10;
		obj->body.position.z = -5;
		break;
	case 7:
		obj->body.position.x = -15;
		obj->body.position.z = -7.5;
		break;
	case 8:
		obj->body.position.x = -15;
		obj->body.position.z = -2.5f;
		break;
	case 9:
		obj->body.position.x = -15;
		obj->body.position.z = 2.5f;
		break;
	case 10:
		obj->body.position.x = -15;
		obj->body.position.z = 7.5;
		break;
	case 11:
		obj->body.position.x = -20;
		obj->body.position.z = -10;
		break;
	case 12:
		obj->body.position.x = -20;
		obj->body.position.z = -5;
		break;
	case 13:
		obj->body.position.x = -20;
		obj->body.position.z = 0;
		break;
	case 14:
		obj->body.position.x = -20;
		obj->body.position.z = 5;
		break;
	case 15:
		obj->body.position.x = -20;
		obj->body.position.z = 10;
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
		if (balls[i].isActive == 0) // false - inactive
		{
			//printf("Not Drawing obj: %d\n", i);
			continue;
		}
		else
		{
			//printf("Drawing obj: %d\n", i);
			drawSphereObject(&balls[i]);
		}
	}
}

void resetWhiteBall()
{
	Vec3 null = { 0, 0, 0 };
	balls[0].body.position.x = 40;
	balls[0].body.position.z = 0;
	balls[0].body.velocity = null;
	balls[0].body.isMoving = 0;
	balls[0].isActive = 1;
	
	printf("Reset White ball");
}
