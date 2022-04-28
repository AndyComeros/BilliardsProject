#ifndef OBJECTFILELIB_H_INCLUDED
#define OBJECTFILELIB_H_INCLUDED
#include <gl/freeglut.h>
#include "VectorMath.h"

//triangles similar to point but ints
typedef int triangle[3];

//OFF file representation
struct OFFFile
{
    char modelName[50];
    int nVert,nFace,nEdge;
    point3D* vertecies;
    triangle* faces;
    point3D center;
};
typedef struct OFFFile OFFFile;

//free offile memory
void freeOFFile(struct OFFFile *off);
//Read in OFF file to a OFFFile struct
void readOFFFile(struct OFFFile *data, char *fileName);
//renders rawOFF object
void renderOFF(struct OFFFile *object3D,vect3D offset,vect3D scale);


void printOFFInfo(struct OFFFile *data);


//3D utilities
void drawAxis();
void drawGridXZ(int size);

#endif // OBJECTFILELIB_H_INCLUDED
