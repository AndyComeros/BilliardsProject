#include "Display.h"
#include <stdio.h>
#include "GUI.h"
#include "GameInput.h"
#include "Texture.h"

#define TIMER 15
#define BALLCOUNT 7
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

static float prevTime = 0;
static float currTime = 0;
static float deltaTime = 0;
static float timeScale = 1000; // converting time into milliseconds
static float camRotAngle = 0;
static int camReset = 1; // for rotation when menu is active


pixel** picture;
void init()
{
	char name[] = { "CoolCid.bmp" };
	picture = InputImage(name,500,500);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	srand(time(0));

	prevTime = glutGet(GLUT_ELAPSED_TIME);

	initGUI();
	InitBilliardUI();
	initGameSession();
	initLights();


}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 10000);

	updateCamera();
	reshapeTexture(w,h);
	reshapeGUI(w,h);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	displayImage(picture,500,500);
	updateCamera();
	adjustLight();
	//drawFlatGrid();
	//drawAngGrid();
	drawBallObjects();
	drawTable();
	
	RenderShotIndicator();
	glClear(GL_DEPTH_BUFFER_BIT);
	//drawAxis();
	renderMenus();

	glutSwapBuffers();
} 

void animate(int value)
{
	glutTimerFunc(TIMER, animate, 0);

	currTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currTime - prevTime) / timeScale;

	if (activeMenu == 1 || activeMenu == 2) 
	{
		camRotAngle += deltaTime / 5;
		cam.pos.y = 100;
		cam.pos.x = sin(camRotAngle) * 100;
		cam.pos.z = cos(camRotAngle) * 100;
		camReset = 1;
	}
	else if (camReset == 1)  // if statement only occurs one through animation
	{
		camRotAngle = 0;
		cam.pos.y = 80;
		cam.pos.x = sin(camRotAngle) * 100;
		cam.pos.z = cos(camRotAngle) * 100;
		camReset = 0; // so camera rotation doesn't get set every frame
	}

	
	
	animateGameObjects(deltaTime);

	prevTime = currTime;

	glutPostRedisplay();
}

void drawAxis()
{
	GLfloat axisCol[][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0} };
	const GLfloat bigNum = 999.0;
	const GLfloat farpointX[] = { bigNum,0.0,0.0 };
	const GLfloat farpointY[] = { 0.0,bigNum,0.0 };
	const GLfloat farpointZ[] = { 0.0,0.0,bigNum };
	const GLfloat origin[] = { 0.0,0.0,0.0 };

	glDisable(GL_LIGHTING);
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
	glEnable(GL_LIGHTING);
}

void drawTable()
{
	
	/*
	* 
	*** floor ***
	* 
	*/
	// green
	Material poolFloor =
	{
		{0.12, 0.50, 0.18, 1.0},
		{0.19, 0.44, 0.0, 1.0},
		{0.55, 0.81, 0.72, 1.0},
		50
	};
	Material poolWall =
	{
		{0.28, 0.14, 0.05, 1.0},
		{0.79, 0.53, 0.34, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		90
	};

	setMaterial(&poolFloor);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH, 0, -FLOORWIDTH);
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH, 0, -FLOORWIDTH);
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH, 0, FLOORWIDTH);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH, 0, FLOORWIDTH);
	glEnd();

	/*
	* 
	*** black cut outs for floor ***
	* 
	*/
	// black
	glDisable(GL_LIGHTING);
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
	glVertex3f(HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-HALFSIZEOFHOLE, 0.25f, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// side left
	glBegin(GL_POLYGON);
	glVertex3f(HALFSIZEOFHOLE, 0.25f, FLOORWIDTH + HALFSIZEOFHOLE);
	glVertex3f(HALFSIZEOFHOLE, 0.25f, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-HALFSIZEOFHOLE, 0.25f, FLOORWIDTH - HALFSIZEOFHOLE);
	glVertex3f(-HALFSIZEOFHOLE, 0.25f, FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	glEnable(GL_LIGHTING);
	/*
	*
	*** line outlines for floor ***
	*
	*/
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// lines
	/*
	glBegin(GL_LINE_LOOP);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0.5f, -FLOORWIDTH - WALLOFFSET);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0.5f, FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0.5f, FLOORWIDTH + WALLOFFSET);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0.5f, -FLOORWIDTH - WALLOFFSET);
	glEnd();
	*/
	



	/*
	* 
	*** back wall ***
	* 
	*/
	// lighter brown
	glColor3f(0.8f, 0.5f, 0.05f);
	setMaterial(&poolWall);
	// front
	
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// right side
	
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// left side
	
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH - WALLOFFSET, 0, FLOORWIDTH - HALFSIZEOFHOLE);
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
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// right side
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, -FLOORWIDTH + HALFSIZEOFHOLE);
	glEnd();
	// left side
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH, 0, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, WALLHEIGHT, FLOORWIDTH - HALFSIZEOFHOLE);
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH + WALLOFFSET, 0, FLOORWIDTH - HALFSIZEOFHOLE);
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
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glVertex3f(-HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glNormal3f(-1, 1, -1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 1, -1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 1, -1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 1, -1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 0, -1);
	glVertex3f(-HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// top side
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 1, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 0, -1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glEnd();
	// bottom side
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, -1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, -1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 0, -1);
	glVertex3f(-HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glNormal3f(-1, 0, -1);
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
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 1, -1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 0, -1);
	glVertex3f(HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, -1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, -1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 0, -1);
	glVertex3f(HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, -1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// top side
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 1, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 0, -1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glEnd();
	// bottom side
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, -1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, -1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, -FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 0, -1);
	glVertex3f(HALFSIZEOFHOLE, 0, -FLOORWIDTH);
	glNormal3f(1, 0, -1);
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
	glNormal3f(-1, 0, 1);
	glVertex3f(-HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 1, 1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 1, 1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 1, 1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 1, 1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 0, 1);
	glVertex3f(-HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// top side
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 1, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glNormal3f(-1, 0, 1);
	glVertex3f(-FLOORLENGTH + HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// bottom side
	glBegin(GL_POLYGON);
	glNormal3f(-1, 1, 1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(-1, 1, 1);
	glVertex3f(-HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 0, 1);
	glVertex3f(-HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glNormal3f(-1, 0, 1);
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
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glNormal3f(1, 0, 1);
	glVertex3f(HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glNormal3f(1, 1, 1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glEnd();
	// redish brown
	glColor3f(0.4f, 0.20f, 0.05f);
	// top
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, 1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, 1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// brown
	glColor3f(0.5f, 0.35f, 0.05f);
	// back
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 1, 1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 0, 1);
	glVertex3f(HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// yellowish brown
	glColor3f(0.5f, 0.5f, 0.05f);
	// top side
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 1, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, FLOORWIDTH);
	glNormal3f(1, 0, 1);
	glVertex3f(FLOORLENGTH - HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glEnd();
	// bottom side
	glBegin(GL_POLYGON);
	glNormal3f(1, 1, 1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH - WALLOFFSET);
	glNormal3f(1, 1, 1);
	glVertex3f(HALFSIZEOFHOLE, WALLHEIGHT, FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 0, 1);
	glVertex3f(HALFSIZEOFHOLE, 0, FLOORWIDTH + WALLOFFSET);
	glNormal3f(1, 0, 1);
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

Camera* getCam()
{
	return &cam;
}
