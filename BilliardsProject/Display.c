#include "Display.h"
#include <stdio.h>

#define STARTING_HEIGHT 10
#define TIMER 15
#define BALLCOUNT 6
#define BONECOUNT 6
#define USER_APPLIED_FORCE 20
#define GRAVITY 9.8

static Camera cam =
{
	{-20, 15, 30},
	{0, 10, 10},
	{0, 1, 0}
};

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
	1 // radius
	}
};

static Object bone = {
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
	}
};

static Vec3 planeP1 = { 2, 0, 2 }, planeP2 = { 1, 0, 1 }, planeP3 = { -1, 0, -1 };

static Face plane = {
	&planeP1,
	&planeP2,
	&planeP3,
	{0},
	{0, 1, 0}
};

static Vec3 planeAngP1 = { 0, 0, 2 }, planeAngP2 =  {-1, -1, -1}, planeAngP3 = {1, 1, 1}; // this isn't correct i think, manually assigned unit normal

static Face planeAng = {
	&planeAngP1,
	&planeAngP2,
	&planeAngP3,
	{0},
	{-1, 1, 0}
};

static Vec3 vectorLeft = { -USER_APPLIED_FORCE, 0.0, 0.0 };
static Vec3 vectorRight = { USER_APPLIED_FORCE, 0.0, 0.0 };
static Vec3 vectorForward = { 0.0, 0.0, -USER_APPLIED_FORCE };
static Vec3 vectorBack = { 0.0, 0.0, USER_APPLIED_FORCE };
static Vec3 vectorUp = { 0.0, USER_APPLIED_FORCE, 0.0 };

static const Vec3 gravity = { 0.0, -GRAVITY, 0.0 };

static float prevTime = 0;
static float currTime = 0;
static float deltaTime = 0;
static float timeScale = 1000; // converting time into milliseconds

Object balls[BALLCOUNT];
Object bones[BONECOUNT];

void loadComplexObj()
{
	//const char* c = getFileName();
	for (int i = 0; i < BALLCOUNT; i++)
	{
		bones[i] = bone;
		loadOffObject("bone.off", &bones[i]);
		for (int j = 0; j < bones[i].off.nFace; j++)
		{
			bones[i].off.faces[j].colour = (GLfloat*)malloc(sizeof(GLfloat)*3);
			randColor(&bones[i].off.faces[j]);
		}
		bones[i].body.radius = radiusOfBoundingSphere(&bones[i].off);
	}
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);

	srand(time(0));

	for (int i = 0; i < BALLCOUNT; i++)
	{
		balls[i] = ball;
		randObjBody(&balls[i]);
	}
	for (int i = 0; i < BONECOUNT; i++)
	{
		randObjBody(&bones[i]);
	}

	planeAng.UnitNormal = normalize(planeAng.UnitNormal);

	prevTime = glutGet(GLUT_ELAPSED_TIME);
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

void randColor(Face* f)
{
	GLfloat c1 = (GLfloat)rand() / (GLfloat)RAND_MAX;
	GLfloat c2 = (GLfloat)rand() / (GLfloat)RAND_MAX;
	GLfloat c3 = (GLfloat)rand() / (GLfloat)RAND_MAX;
	f->colour[0] = c1;
	f->colour[1] = c2;
	f->colour[2] = c3;
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		cam.pos.x, cam.pos.y, cam.pos.z,
		cam.look.x, cam.look.y, cam.look.z,
		cam.up.x, cam.up.y, cam.up.z);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
	case 'D':
		applyForceToAllObjects(&balls, BALLCOUNT, &vectorRight);
		applyForceToAllObjects(&bones, BONECOUNT, &vectorRight);
		break;
	case 'w':
	case 'W':
		applyForceToAllObjects(&balls, BALLCOUNT, &vectorForward);
		applyForceToAllObjects(&bones, BONECOUNT, &vectorForward);
		break;
	case 's':
	case 'S':
		applyForceToAllObjects(&balls, BALLCOUNT, &vectorBack);
		applyForceToAllObjects(&bones, BONECOUNT, &vectorBack);
		break;
	case 'a':
	case 'A':
		applyForceToAllObjects(&balls, BALLCOUNT, &vectorLeft);
		applyForceToAllObjects(&bones, BONECOUNT, &vectorLeft);
		break;
	case ' ':
		applyForceToAllObjects(&balls, BALLCOUNT, &vectorUp);
		applyForceToAllObjects(&bones, BONECOUNT, &vectorUp);
		applyForceToAllObjects(&bones, BONECOUNT, &vectorUp);
		break;
	case 'Q':
	case 'q':
		for (int i = 0; i < BONECOUNT; i++)
		{
			FreeObject(&bones[i].off);
		}
		exit(0);
	default:
		break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawFlatGrid();
	drawAngGrid();
	//drawBallObjects();
	drawBoneObjects();

	glutSwapBuffers();
}

void animate(int value)
{
	glutTimerFunc(TIMER, animate, 0);

	currTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currTime - prevTime) / timeScale;

	for (int i = 0; i < BALLCOUNT; i++)
	{
		applyForce(&balls[i], gravity); // gravity
		rotateObjects(&balls[i]);
		if (DistanceBetweenObjPlane(&balls[i], &plane) < 1.0f)
		{
			resolveCollisionObjPlane(&balls[i], &plane);
		}
		updateObject(&balls[i], deltaTime);
	}

	for (int i = 0; i < BONECOUNT; i++)
	{
		//if (DistanceBetweenObjPlane(&bones[i], &plane) > 1.0f)
		{
			applyForce(&bones[i], gravity); // gravity
			rotateObjects(&bones[i]);
		}
		if (DistanceBetweenObjPlane(&bones[i], &planeAng) < 1.0f)
		{
			//resolveCollisionObjPlane(&bones[i], &plane); // this is getting called again before bounce gets past threshold
			bones[i].body.velocity = collisionResolution(&bones[i].body.velocity, &planeAng.UnitNormal);
		}
		if (DistanceBetweenObjPlane(&bones[i], &plane) < 1.0f)
		{
			//resolveCollisionObjPlane(&bones[i], &plane); // this is getting called again before bounce gets past threshold
			bones[i].body.velocity = collisionResolution(&bones[i].body.velocity, &plane.UnitNormal);
		}
		updateObject(&bones[i], deltaTime);
	}

	prevTime = currTime;

	/*for (int i = 0; i < BALLCOUNT; i++)
	{
		updatePrevObject(&balls[i]);
	}
	for (int i = 0; i < BONECOUNT; i++)
	{
		updatePrevObject(&bones[i]);
	}*/

	printf("Accel %f\nVel: %f\n", bones[1].body.acceleration.y, bones[1].body.velocity.y);

	glutPostRedisplay();
}

void drawFlatGrid()
{
	GLfloat i = 0.0, j = 0.0;
	GLint maxSize = 100;
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex3f(-maxSize, 0, -maxSize);
	glVertex3f(-maxSize, 0, maxSize);
	glVertex3f(maxSize, 0, maxSize);
	glVertex3f(maxSize, 0, -maxSize);
	glEnd();

	//for (i = 0.0; i < maxsize; i++)
	//{
	//	 z direction
	//	glBegin(GL_LINES);
	//	glVertex3f(i * 2 - maxsize / 2, 0.0, 0.0 - maxsize / 2);
	//	glVertex3f(i * 2 - maxsize / 2, 0.0, 1'000.0);
	//	glEnd();

	//	 x direction
	//	glBegin(GL_LINES);
	//	glVertex3f(0.0 - maxsize / 2, 0.0, i * 2.0 - maxsize / 2);
	//	glVertex3f(1'000.0, 0.0, i * 2.0 - maxsize / 2);
	//	glEnd();
	//}
}

void drawAngGrid()
{
	GLfloat i = 0.0;
	GLint maxSize = 100;
	GLfloat halfMaxSize = maxSize / 2;
	glColor3f(1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex3f(-maxSize, -maxSize, -maxSize);
	glVertex3f(-maxSize, -maxSize, maxSize);
	glVertex3f(maxSize, maxSize, maxSize);
	glVertex3f(maxSize, maxSize, -maxSize);
	glEnd();

	/*for (i = 0.0; i < maxSize; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(-1000, -1000, -halfMaxSize + i);
		glVertex3f(1000, 1000, -halfMaxSize + i);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-halfMaxSize +i, -halfMaxSize +i, -halfMaxSize);
		glVertex3f(-halfMaxSize +i, -halfMaxSize +i, halfMaxSize);
		glEnd();
	}*/

}

void drawBallObjects()
{
	for (int i = 0; i < BALLCOUNT; i++)
	{
		drawSphereObject(&balls[i]);
	}
}

void drawBoneObjects()
{
	for (int i = 0; i < BALLCOUNT; i++)
	{
		drawComplexObject(&bones[i]);
	}
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

void applyForceToAllObjects(Object* obj, int max, Vec3* f)
{
	for (int i = 0; i < max; i++)
	{
		applyForce(&obj[i], *f);
	}
}
