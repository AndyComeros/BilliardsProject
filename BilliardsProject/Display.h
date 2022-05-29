#pragma once

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <GL\freeglut.h>
#include "GameSession.h"

typedef struct {
	Vec3 pos;// position
	Vec3 look; // lookat
	Vec3 up; // up vector
}Camera;

void init();

void reshape(int w, int h);

void display();
void animate(int value);

void drawTable();

void updateCamera();

#endif // DISPLAY_H_INCLUDED
