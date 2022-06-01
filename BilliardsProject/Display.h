#pragma once

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <GL\freeglut.h>
#include "GameSession.h"
#include "Lighting.h"

typedef struct {
	Vec3 pos;// position
	Vec3 look; // lookat
	Vec3 up; // up vector
}Camera;

void init();

void reshape(int w, int h);

void display();
void animate(int value);
void drawAxis();
void drawTable();

void updateCamera();
void drawCue(Vec3 start, Vec3 end);
#endif // DISPLAY_H_INCLUDED
