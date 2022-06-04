#pragma once

#ifndef OFFFILE_H_INCLUDED
#define OFFFILE_H_INCLUDED

#include "Face.h"

/**
*	@brief Stores OFF file 3D data
*/
typedef struct OffModel {
		///faces of the 3d model
	Face* faces;
		///Positions of each vertex in the model
	Vec3* vertice;
		///Amount of faces, vertecies and edges
	int nVert, nFace, nEdge;
}OffModel;
/**
*	@brief gets a fileName from the user a
*	@return char* - array of characters representing the file name
*/
const char* getFileName();
/**
*	@brief reads in an OFF file and stores its data in an Objects 3D data
*	@param fileName - path of the OFF file
*	@param obj - object storing the OFF data
*	@return void
*/
void readOffFile(char *filename, OffModel *obj);
/**
*	@brief Frees up an objects memory
*	@param obj - object having its memory freed\
*	@return void
*/
void FreeObject(OffModel *obj);

#endif // !OFFFILE_H_INCLUDED

