#ifndef OFFFILE_H_INCLUDED
#define OFFFILE_H_INCLUDED
#include <gl/freeglut.h>
#include "Triangles.h"

//triangles similar to point but ints
typedef int triangle[3];

//OFF file representation
typedef struct
{
    char modelName[50];
    int nVert,nFace,nEdge;
    Vec3* vertecies;
    triangle* faces;
    Vec3 center;
}OFFFile;

//free offile memory
void freeOFFile(OFFFile *off);
//Read in OFF file to a OFFFile struct
void readOFFFile(OFFFile *data, char *fileName);
//renders rawOFF object
void renderOFF(OFFFile *object3D,Vec3 offset,Vec3 scale);


void printOFFInfo(OFFFile *data);

#endif // OFFFILE_H_INCLUDED
