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
    point3D* vertecies;
    triangle* faces;
    point3D center;
}OFFFile;

//free offile memory
void freeOFFile(OFFFile *off);
//Read in OFF file to a OFFFile struct
void readOFFFile(OFFFile *data, char *fileName);
//renders rawOFF object
void renderOFF(OFFFile *object3D,vect3D offset,vect3D scale);


void printOFFInfo(OFFFile *data);


//3D utilities
void drawAxis();
void drawGridXZ(int size);

#endif // OFFFILE_H_INCLUDED