#pragma once

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "GL\freeglut.h"
#include "Vector.h"

typedef struct {
	Vec3 pos; // Camera position
	Vec3 look; // Look at position
	Vec3 up; // Camera up vector
}Camera;

void viewingInit();


#endif