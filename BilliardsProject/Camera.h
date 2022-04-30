#pragma once

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "GL\freeglut.h"
#include "Vector.h"


typedef struct{
	GLdouble fov;		// degrees
	GLdouble aspect;		// aspect ratio aspect = height/width
	GLdouble nearVal;     // near and far clipping planes
	GLdouble farVal;
}CameraViewing;

typedef struct{
	Vec3 pos; // Camera position
	Vec3 look; // Look at position
	Vec3 up; // Camera up vector
}Camera;

void initCam(const Camera *c);
void updateCameraViewing(const CameraViewing *c);
void updateCamera(const Camera *c);

#endif