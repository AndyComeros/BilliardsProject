#ifndef VECTORMATH_H_INCLUDED
#define VECTORMATH_H_INCLUDED

#include <gl/freeglut.h>


    //point and vector are interchangeable
    typedef GLfloat point3D[3];
    typedef point3D vect3D;

    void vectFromPoints(vect3D v,point3D p1, point3D p2);

    //all void vector methods modifies v1.
    //vector x scalar
    void vectMultScalar(vect3D * v, GLfloat s);
    void vectMultScalars(vect3D * v, GLfloat sx,GLfloat sy,GLfloat sz);
    //vect add scalar
    void vectAddScalar(vect3D * v, GLfloat s);
    void vectAddScalars(vect3D * v, GLfloat ax,GLfloat ay,GLfloat az);
    void vectAddVect(vect3D * v1, vect3D v2);
    //dot product
    GLfloat vectDotProd(vect3D v1, vect3D v2);
    //cross product
    void vectCrossProd(vect3D * v1, vect3D v2);


    //normal vector
    void vectNormal(vect3D * rtrnVect, vect3D v1,vect3D v2);
    //normalizes vector/unit normals
    void vectNormalize(vect3D * v1);
    GLfloat vectMagnitude(vect3D v);


    //triangleStuff
    GLfloat triangleArea(point3D p1, point3D p2,point3D p3);
    void triangleNormal(vect3D * v,point3D p1, point3D p2,point3D p3);
    void triangleUnitNormal(vect3D * v,point3D p1, point3D p2,point3D p3);

#endif // VECTORMATH_H_INCLUDED
