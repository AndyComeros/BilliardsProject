
#include <gl/freeglut.h>
#include "Vector.h"
#include "math.h"

#include<stdio.h>
//using namespace std;

//gets vector between two points. form p1 to p2
vect3D vectMinus(vect3D p1, vect3D p2)
{
    vect3D v;
    v.x =  (p1.x - p2.x);
    v.y =  (p1.y - p2.y);
    v.z =  (p1.z - p2.z);
    return v;
}
vect3D vectMultScalar(vect3D v1, GLfloat s)
{
    vect3D v;
    v.x = v1.x*s;
    v.y = v1.y*s;
    v.z = v1.z*s;
    return v;
}
vect3D vectMultScalars(vect3D v1, GLfloat sx,GLfloat sy,GLfloat sz)
{
    vect3D v;
    v.x = v1.x*sx;
    v.y = v1.y*sy;
    v.z = v1.z*sz;
    return v;
}

vect3D vectAddScalar(vect3D v1, GLfloat s)
{
    vect3D v;
    v.x = v1.x+s;
    v.y = v1.y+s;
    v.z = v1.z+s;
    return v;
}
vect3D vectAddScalars(vect3D v1, GLfloat ax,GLfloat ay,GLfloat az)
{
    vect3D v;
    v.x = v1.x+ax;
    v.y = v1.y+ay;
    v.z = v1.z+az;
    return v;
}

vect3D vectAddVect(vect3D v1, vect3D v2)
{
    vect3D v;
    v.x = v1.x+v2.x;
    v.y = v1.y+v2.y;
    v.z = v1.z+v2.z;
    return v;
}

GLfloat vectDotProd(vect3D v1, vect3D v2)
{
    return v1.x * v2.x+
           v1.y * v2.y+
           v1.z * v2.z;
}

vect3D vectCrossProd(vect3D v1, vect3D v2)
{
    vect3D nV;
    nV.x = (v1.y * v2.z) - (v1.z * v2.y);
    nV.y = (v1.z * v2.x) - (v1.x * v2.z);
    nV.z = (v1.x * v2.y) - (v1.y * v2.x);
    return nV;
}

GLfloat vectMagnitude(vect3D v)
{
    GLfloat length = sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
    return length;
}

vect3D vectNormalize(vect3D v1)
{
    GLfloat length = vectMagnitude(v1);
    v1.x /= length;
    v1.y /= length;
    v1.z /= length;
}

GLfloat triangleArea(point3D p1, point3D p2,point3D p3)
{
    vect3D vect1 = vectMinus(p1,p2);
    vect3D vect2 = vectMinus(p1,p3);
    vect3D vect3 = vectCrossProd(vect1,vect2);
    GLfloat area = vectMagnitude(vect3);
    area /= 2;
    return area;
}

//not tested
vect3D triangleNormal(point3D p1, point3D p2,point3D p3)
{
    vect3D vect1 = vectMinus(p1,p2);
    vect3D vect2 = vectMinus(p1,p3);

    return vectCrossProd(vect1,vect2);
}

//not tested
vect3D triangleUnitNormal(point3D p1, point3D p2,point3D p3)
{
    vect3D v = triangleNormal(p1,p2,p3);
    v = vectNormalize(v);
    return v;
}
