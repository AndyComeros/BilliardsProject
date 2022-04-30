#pragma once

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <gl\freeglut.h>
#include "GameObject.h"
#include "Camera.h"

void initGlut();

void initObjects();

void display(void);
void PhysicsUpdate(int num);
//3D utilities
void drawAxis();
void drawGridXZ(int size);

void collideBallz(GameObject* b1, GameObject* b2);

#endif // DISPLAY_H_INCLUDED