#pragma once

#ifndef OFFFILE_H_INCLUDED
#define OFFFILE_H_INCLUDED

#include "Face.h"

typedef struct OffModel {
	Face* faces;
	Vec3* vertice;
	int nVert, nFace, nEdge;
}OffModel;

const char* getFileName();

void readOffFile(char *filename, OffModel *obj);

void FreeObject(OffModel *obj);

#endif // !OFFFILE_H_INCLUDED

