#pragma once

#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED

#include <gl/freeglut.h>
#include "GUI.h"//creates GUI elements 
#include "Object.h"//interracts with game objects
#include "Display.h"//temp include for testing
#include <stdio.h>

#define INPUT_SENSITIVITY 0.1
//###############--DATA_MEMBERS--###############//

//object adding force to
Body *cueBall;
//force to be added to cueBall
GLfloat cueForce;
//angle of ball
GLfloat cueAngle;
//is ball hittable;
int isHittable;

//whether ball inputs are currently being taken
//unsigned int isBallHittable = 1;

//###############--FUNCTION_MEMBERS--###############//

//init the gameInput data, takes in reference to cueBall. put in init function
void initGameInput(Object *n_CueBall);

//callback for keyboard special key input for ball hitting, put in keyboard callback function(or as the callback function)
void shotInputSpecialKeyBoard(unsigned char key, int x, int y);

//callback for normal key input
void shotInputKeyBoard(unsigned char key, int x, int y);

//put in display function, renders the angle/power indicator to screen
void RenderShotIndicator();

//calculates end of output line
Vec3 calcEndPoint(float lengthMod);

//calculates vector used to move ball
Vec3 calcForceVector();
void clickInput(int Button, int state, int x, int y);
void cueDisplay(int x, int y);

void setCamRotAngle(GLfloat a);

#endif