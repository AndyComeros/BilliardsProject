#pragma once

#include "Lighting.h"




void initLights()
{
	
	GLfloat lightPos1[] = { 1.0,1.0,1.0,0.0 };
	GLfloat lightDir1[] = { 0.0,-1.0,0.0,0.0 };
	GLfloat colWhite[] = {1.0,0.0,0.0,1.0};
	GLfloat colRed[] = {1.0,1.0,1.0,1.0};
	GLfloat colGrey[] = {0.1,0.1,0.1,1.0};

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//light settings:
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir1);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, colGrey);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, colRed);
	//(GL_LIGHT0, GL_SPECULAR, colWhite);

}

void setMaterial(Material * material) 
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &material->alpha);

}