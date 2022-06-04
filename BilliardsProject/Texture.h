#pragma once
#include <GL\freeglut.h>
#include <stdio.h>
#include <stdlib.h>
	///Value of a RGB pixel value
typedef unsigned char pixel[3];	
	/**
	*	@brief Reads in an image file and returns it as a 2D array of pixel values
	*	@param fileName - file path of image
	*	@param width - width of image
	*	@param height - height of image
	*	@return pixel** - 2D array of pixels
	*/
pixel** InputImage(char* fileName, int width, int height);
	/**
	*	@brief diplays a 2D array of pixels as 2D image at a specified window position
	*	@param imageDate - image data
	*	@param w - image width
	*	@param h - image height
	*	@param x - x position rendered at
	*	@param y - y position renered at
	*/
void displayImage(pixel** imageData, int w, int h, int x, int y);
	/**
	*	@brief The reshape callback for images, ensures images are diaplyed correctly aftera window resize
	*	@param w - new window width
	*	@param h - new window height
	*/
void reshapeTexture(int w, int h);