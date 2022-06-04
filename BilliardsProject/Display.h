#pragma once

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <GL\freeglut.h>
#include "GameSession.h"
#include "Lighting.h"
/**
*	@breif Stores information for a camera position in the scene
*/
typedef struct {
		/// Camera position
	Vec3 pos;
		///Camera look position
	Vec3 look;
		///Camera up vector
	Vec3 up;
}Camera;
	/**
	*	@brief Initializes display function variables. Call before entering glut main loop
	*	@return void
	*/
void init();
	/**
	*	@brief contains several reshape functions for different items, including GUI reshape, Texture and camera.
	*	Ensures that everything is rendered correctly in relation to the window size. Set as callback in the
	*	glutReshapeFunc.
	*	@param w - new window width
	*	@param h - new window height
	*/
void reshape(int w, int h);
	/**
	*	@brief Main glutDisplay callback function. Renders all billiards game elemets when called
	*	@return void
	*/
void display();
	/**
	*	@brief modifies all objects in the scenes values based on the last time this function was called.
	*	this is the main game update loop. Call this function in the glutTimer func to begin the main physics
	*	and animation loop.
	*	@param - value, parameter reqired for glutTimerFunc callback
	*	@return void
	*/
void animate(int value);
	/**
	*	@brief useful debug function. Displays the XYZ axis centered at 0,0,0
	*	@return void
	*/
void drawAxis();
	/**
	*	@brief Renders a billiards table. all values and normals are hardcoded into the function.
	*	@return void
	*/
void drawTable();
	/**
	*	@brief Sets up the cameras position based on the globally stored camera values
	*	@return void
	*/
void updateCamera();
	/**
	*	@brief returns a poiter to the scenes main camera information
	*	@return Camera* pointer to the scenes main camera
	*/
Camera* getCam();

#endif // DISPLAY_H_INCLUDED
