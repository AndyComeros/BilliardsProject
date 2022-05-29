#pragma once

#include "Lighting.h"

GLfloat lightPos1[] = { 1.0,1.0,0.0,0.0 };
GLfloat lightDir1[] = { -0.2,-1.0,0.0,0.0 };


void initLights()
{
	

	GLfloat colWhite[] = {1.0,0.0,0.0,1.0};
	GLfloat colRed[] = {0.5,0.3,0.3,1.0};
	GLfloat colGrey[] = {0.2,0.2,0.2,1.0};

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//light settings:
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, colGrey);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, colRed);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);//normalizes norms-expensive...
	//(GL_LIGHT0, GL_SPECULAR, colWhite);

}

void setMaterial(Material * material) 
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &material->alpha);

}
void adjustLight() {


	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir1);

}