#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <gl/freeglut.h>

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vec3;


Vec3 vectMinus(Vec3 p1, Vec3 p2);

Vec3 vectMultScalar(Vec3 v1, GLfloat s);
Vec3 vectMultScalars(Vec3 v1, GLfloat sx,GLfloat sy,GLfloat sz);

Vec3 vectAddScalar(Vec3 v1, GLfloat s);
Vec3 vectAddScalars(Vec3 v1, GLfloat ax,GLfloat ay,GLfloat az);

Vec3 vectAddVect(Vec3 v1, Vec3 v2);

GLfloat vectDotProd(Vec3 v1, Vec3 v2);

Vec3 vectCrossProd(Vec3 v1, Vec3 v2);

GLfloat vectMagnitude(Vec3 v);

Vec3 vectNormalize(Vec3 v1);


#endif // VECTOR_H_INCLUDED
