#pragma once
#include <GL/freeglut.h>
	/**
	*	@brief lighting material properties used in the Phong
	*	reflection model lighting.
	*/
typedef struct Material 
{
		///Ambient light of material
	GLfloat ambient[4];
		///Diffuse light of material
	GLfloat diffuse[4];
		///Specular light of material
	GLfloat specular[4];
		///"Shinyness" of material
	GLfloat alpha;
} Material;
	/**
	*	@brief sets up basic lighting setup with global light  pointing downwards.
	*	Call in main initailize method.
	*	@return void
	*/
void initLights();
	/**
	*	@brief	Sets the current material being used to render.
	*	@param	material - material values for current material
	*	@return	void
	*/
void setMaterial(Material * material);
	/**
	*	@brief Ensures the light is relative to worldspace rather than the camera
	*	call this function in the Display method.
	*	@return void
	*/
void adjustLight();