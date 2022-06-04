#pragma once

#include "Lighting.h"


GLfloat lightPos1[] = {0.0,1.0,0.0,0.0};
GLfloat lightDir1[] = {0.0,-1.0,0.0,0.0};

void initLights()
{

	GLfloat defaultSpec[] = {1.0,1.0,1.0,1.0};
	GLfloat defaultDiff[] = {0.5,0.3,0.4,1.0};
	GLfloat defaultAmbi[] = {0.3,0.3,0.3,1.0};

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//light settings:
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, defaultAmbi);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, defaultDiff);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);//normalizes norms-expensive...
	(GL_LIGHT0, GL_SPECULAR, defaultSpec);

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