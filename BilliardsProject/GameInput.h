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
///Object adding force to
Body *cueBall;
///Force to be added to cueBall
GLfloat cueForce;
///Angle of force is added to cue ball
GLfloat cueAngle;
///If the cue ball can currently be interracted with by the user
int isHittable;
// To Tell
static int inGame = 0;

//whether ball inputs are currently being taken
//unsigned int isBallHittable = 1;

//###############--FUNCTION_MEMBERS--###############//
	/**
	*	@brief initializes all default Game input values and sets the Cue ball
	*	@param	n_CueBall - ball the user will interract with
	*	@return	void
	*/
void initGameInput(Object *n_CueBall);
	/**
	*	@brief Keyboard callback functions for registering ball input actions
	*	register callback in glutKeyboardFunc method
	*	@param	key - key being pressed
	*	@param	x - mouse x coord
	*	@param	y - mouse y coord
	*	@return	void
	*/
void shotInputSpecialKeyBoard(unsigned char key, int x, int y);
	/**
	*	@brief Keyboard special keys callback functions for registering ball input actions
	*	register callback in glutSpecialFunc method
	*	@param	key - key being pressed
	*	@param	x - mouse x coord
	*	@param	y - mouse y coord
	*	@return	void
	*/
void shotInputKeyBoard(unsigned char key, int x, int y);
	/**
	*	@brief Renders the shot indicator that indicates the velocity vector of the cueball
	*	call this function in the main display method.
	*	@return void
	*/
void RenderShotIndicator();
	/**
	*	@brief calculates the position of the end of the shot indicator, modifies the length from the
	*	cue ball by a factor for better visibility.
	*	@param lengthMod - factor the lenght the returned posiiton is away from the cueballs origin
	*	@param angle - angle the point is relative to the CueBall
	*	@return Vec3 - position of point based on cueForce and angle
	*/
Vec3 calcEndPoint(float lengthMod, float angle);
	/**
	*	@brief calculates the velocity the cue ball will be set to based on
	*	the global cueForce and cueAngle
	*	@return Vec3 - vector created between the cue balls posiiton and the shot indicators end.
	*/
Vec3 calcForceVector();
	/**
	*	@brief Mouse input callback function, used for ball mouse input. Register in the glutMouseFunc callback
	*	@param	Button - mouse button being pressed
	*	@param	State - state of mouse button being pressed
	*	@param	x - mouse x coord
	*	@param	y - mouse y coord
	*	@return	void
	*/
void clickInput(int Button, int state, int x, int y);	
	/**
	*	@brief diaply function for shot indicator when mouse input is being used
	*	@param x - mouse X coord
	*	@param y - mouse y coord
	*/
void cueMovement(int x, int y);
	/**
	*	@brief changes the angle the camera is rotated around 0,0,0 
	*	along the Y axis
	*	@param a - new angle
	*	@return void
	*/
void setCamRotAngle(GLfloat a);
	/**
	*	@brief returns a Vec3 which represents the direction of the mouse click
	*	@param x - mouse X coord
	*	@param y - mouse y coord
	*	@return Vec3
	*/
Vec3 rayCast(int x, int y);
#endif