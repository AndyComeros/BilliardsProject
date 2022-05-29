#pragma once
#include <gl/freeglut.h>



typedef struct Material 
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat alpha;
} Material;


void initLights();

void setMaterial(Material * material);
void adjustLight();