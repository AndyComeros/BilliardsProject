#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <gl/freeglut.h>

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vect3D;
typedef vect3D point3D;

vect3D vectMinus(vect3D p1, vect3D p2);

vect3D vectMultScalar(vect3D v1, GLfloat s);
vect3D vectMultScalars(vect3D v1, GLfloat sx,GLfloat sy,GLfloat sz);

vect3D vectAddScalar(vect3D v1, GLfloat s);
vect3D vectAddScalars(vect3D v1, GLfloat ax,GLfloat ay,GLfloat az);

vect3D vectAddVect(vect3D v1, vect3D v2);

GLfloat vectDotProd(vect3D v1, vect3D v2);

vect3D vectCrossProd(vect3D v1, vect3D v2);

GLfloat vectMagnitude(vect3D v);


vect3D vectNormalize(vect3D v1);

GLfloat triangleArea(point3D p1, point3D p2,point3D p3);
vect3D triangleNormal(point3D p1, point3D p2,point3D p3);
vect3D triangleUnitNormal(point3D p1, point3D p2,point3D p3);

#endif // VECTOR_H_INCLUDED
