#pragma once

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <GL\freeglut.h>
#include "Object.h"
#include "Physics.h"

typedef struct {
	Vec3 pos;// position
	Vec3 look; // lookat
	Vec3 up; // up vector
}Camera;

void loadComplexObj();
void init();
void randObjBody(Object* obj);
void randColor(Face* f);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

void display();
void animate(int value);

void drawFlatGrid();
void drawAngGrid();
void drawBallObjects();
void drawBoneObjects();
void rotateObjects(Object* obj);

void applyForceToAllObjects(Object* obj, int max, Vec3* f);

#endif // DISPLAY_H_INCLUDED
