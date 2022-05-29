#include "Display.h"
#include <stdio.h>
#include "GUI.h"
#include "GameInput.h"

#define STARTING_HEIGHT 10
#define TIMER 15
#define BALLCOUNT 7
#define BONECOUNT 2
#define USER_APPLIED_FORCE 20
#define GRAVITY 9.8
#define FLOORWIDTH 50.f
#define FLOORLENGTH 75.f
#define WALLHEIGHT 5.f
#define HALFSIZEOFHOLE 5.f
#define WALLOFFSET 1.f
#define WALLWIDTH 5.f

static Camera cam =
{
	{100, 100, 100},
	{0, 0, 0},
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
		testObjBody(&balls[i],i);
	}
	for (int i = 0; i < BONECOUNT; i++)
	{
		testObjBody(&bones[i],i);
	}

	planeAng.UnitNormal = normalize(planeAng.UnitNormal);

	prevTime = glutGet(GLUT_ELAPSED_TIME);

	initGUI();
	InitBilliardUI();
	initGameInput(&balls[0]);
}

void testObjBody(Object* obj,int index) {
	
	obj->body.radius = 2;
	obj->body.mass = 3;
	obj->isAvtive = 0;
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

	updateCamera();

	reshapeGUI(w,h);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	updateCamera();
	//drawFlatGrid();
	//drawAngGrid();
	drawBallObjects();
	//drawBoneObjects();
	drawTable();
	
	
	
	RenderShotIndicator();
	glClear(GL_DEPTH_BUFFER_BIT);
	//drawAxis();
	renderMenus();

	glutSwapBuffers();
}

float rotAngle = 0;
void animate(int value)
{
	glutTimerFunc(TIMER, animate, 0);

	currTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currTime - prevTime) / timeScale;

	
	if(activeMenu == 1 || activeMenu == 2) {
		rotAngle += deltaTime / 5;
		cam.pos.y = 100;
	}
	else {
		rotAngle = 0;
		cam.pos.y = 80;
	}

	cam.pos.x = sin(rotAngle) * 100;
	cam.pos.z = cos(rotAngle) * 100;


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
		if (balls[i].isAvtive != 0) {
			activeCount++;
			isHittable = 0;
		}
			
		for (size_t j = i+1; j < BALLCOUNT; j++)
		{
			physicSphereCollide(&balls[i].body,&balls[j].body);
		}
		//rotate balls. not final, not sure if correct but looks convining
		balls[i].body.rotation = normalize(balls[i].body.velocity);
		balls[i].body.rotAngle += length(balls[i].body.velocity);
	}

	if (activeCount == 0 && activeMenu == 3) {
		isHittable = 1;
	}

	prevTime = currTime;

	glutPostRedisplay();
}

void drawFlatGrid()
{
	GLfloat i = 0.0, j = 0.0;
	GLint maxSize = 100;
	glColor3f(1.0, 1.0, 1.0);

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

void drawAxis()
{
	GLfloat axisCol[][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0} };
	const GLfloat bigNum = 999.0;
	const GLfloat farpointX[] = { bigNum,0.0,0.0 };
	const GLfloat farpointY[] = { 0.0,bigNum,0.0 };
	const GLfloat farpointZ[] = { 0.0,0.0,bigNum };
	const GLfloat origin[] = { 0.0,0.0,0.0 };

	glLineWidth(3.0);
	glBegin(GL_LINES);

	glColor3fv(axisCol[0]);
	glVertex3fv(origin);
	glVertex3fv(farpointX);

	glColor3fv(axisCol[1]);
	glVertex3fv(origin);
	glVertex3fv(farpointY);

	glColor3fv(axisCol[2]);
	glVertex3fv(origin);
	glVertex3fv(farpointZ);
	glEnd();
}

void drawTable()
{
	
	/*
	* 
	*** floor ***
	* 
	*/
	// green
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH, 0, -FLOORWIDTH);
	glVertex3f(-FLOORLENGTH, 0, FLOORWIDTH);
	glVertex3f(FLOORLENGTH, 0, FLOORWIDTH);
	glVertex3f(FLOORLENGTH, 0, -FLOORWIDTH);
	glEnd();

	/*
	* 
	*** black cut outs for floor ***
	* 
	*/
	// black
	glColor3f(0.0, 0.0, 0.0);
	// top right
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// top left
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0.25f, FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0.25f, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - HALFSIZEOFHOLE, 0.25f, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - HALFSIZEOFHOLE, 0.25f, FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// bottom right
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH + HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// bottom left
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH + HALFSIZEOFHOLE, 0.25f, FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + HALFSIZEOFHOLE, 0.25f, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0.25f, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0.25f, FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// side right
	glBegin(GL_POLYGON);
	glVertex3f(-HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// side left
	glBegin(GL_POLYGON);
	glVertex3f(-HALFSIZEOFHOLE, 0.25f, FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-HALFSIZEOFHOLE, 0.25f, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(HALFSIZEOFHOLE, 0.25f, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(HALFSIZEOFHOLE, 0.25f, FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();

	/*
	*
	*** line outlines for floor ***
	*
	*/
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// lines
	glBegin(GL_LINE_LOOP);
	glVertex3f(-FLOORLENGTH, 0.5f, -FLOORWIDTH);
	glVertex3f(-FLOORLENGTH, 0.5f, FLOORWIDTH);
	glVertex3f(FLOORLENGTH, 0.5f, FLOORWIDTH);
	glVertex3f(FLOORLENGTH, 0.5f, -FLOORWIDTH);
	glEnd();
	

	/*
	* 
	*** back wall ***
	* 
	*/
	// lighter brown
	glColor3f(0.8f, 0.5f, 0.05f);
	// front
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// right side
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// left side
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glEnd();


	/*
	* 
	*** front wall ***
	* 
	*/
	// lighter brown
	glColor3f(0.8f, 0.5f, 0.05f);
	// font
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// right side
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// left side
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glEnd();

	/* 
	* 
	*** right wall ***
	* 
	*/
	/*
	*
	*** top right wall ***
	*
	*/
	// lighter brown
	glColor3f(0.8f, 0.5f, 0.05f);
	// font
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(-HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// top side
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glEnd();
	// bottom side
	glBegin(GL_POLYGON);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(-HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glEnd();
	/*
	*
	*** bottom right wall ***
	*
	*/
	// lighter brown
	glColor3f(0.8f, 0.5f, 0.05f);
	// front
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// top side
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glEnd();
	// bottom side
	glBegin(GL_POLYGON);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glEnd();


	/*
	*
	*** left wall ***
	* 
	*/
	/*
	*
	*** top left wall ***
	*
	*/
	// lighter brown
	glColor3f(0.8f, 0.5f, 0.05f);
	// front
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glVertex3f(-HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// top side
	glBegin(GL_POLYGON);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glEnd();
	// bottom side
	glBegin(GL_POLYGON);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glVertex3f(-HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glEnd();
	/*
	*
	*** bottom left wall ***
	*
	*/
	// lighter brown
	glColor3f(0.8f, 0.5f, 0.05f);
	// front
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glVertex3f(HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// top side
	glBegin(GL_POLYGON);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glEnd();
	// bottom side
	glBegin(GL_POLYGON);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glVertex3f(HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glEnd();
}


void updateCamera() 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		cam.pos.x, cam.pos.y, cam.pos.z,
		cam.look.x, cam.look.y, cam.look.z,
		cam.up.x, cam.up.y, cam.up.z);
}
