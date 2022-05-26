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

//temp
void testObjBody(Object* obj, int index);

void randObjBody(Object* obj);
void randColor(Face* f);
void reshape(int w, int h);

void display();
void animate(int value);

void drawFlatGrid();
void drawAngGrid();
void drawBallObjects();
void rotateObjects(Object* obj);

void drawAxis();

void drawTable();

#endif // DISPLAY_H_INCLUDED
