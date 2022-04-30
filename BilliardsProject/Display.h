#pragma once

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <gl\freeglut.h>
#include "GameObject.h"

void initGlut();
void changeSize(int w, int h);

void initObjects();

void display(void);
void PhysicsUpdate(int num);

#endif // DISPLAY_H_INCLUDED