
#include <gl/freeglut.h>
#include "Vector.h"
#include "math.h"

#include<stdio.h>
//using namespace std;

//gets vector between two points. form p1 to p2
Vec3 vectMinus(Vec3 p1, Vec3 p2)
{
    Vec3 v;
    v.x =  (p1.x - p2.x);
    v.y =  (p1.y - p2.y);
    v.z =  (p1.z - p2.z);
    return v;
}
Vec3 vectMultScalar(Vec3 v1, GLfloat s)
{
    Vec3 v;
    v.x = v1.x*s;
    v.y = v1.y*s;
    v.z = v1.z*s;
    return v;
}
Vec3 vectMultScalars(Vec3 v1, GLfloat sx,GLfloat sy,GLfloat sz)
{
    Vec3 v;
    v.x = v1.x*sx;
    v.y = v1.y*sy;
    v.z = v1.z*sz;
    return v;
}

Vec3 vectAddScalar(Vec3 v1, GLfloat s)
{
    Vec3 v;
    v.x = v1.x+s;
    v.y = v1.y+s;
    v.z = v1.z+s;
    return v;
}
Vec3 vectAddScalars(Vec3 v1, GLfloat ax,GLfloat ay,GLfloat az)
{
    Vec3 v;
    v.x = v1.x+ax;
    v.y = v1.y+ay;
    v.z = v1.z+az;
    return v;
}

Vec3 vectAddVect(Vec3 v1, Vec3 v2)
{
    Vec3 v;
    v.x = v1.x+v2.x;
    v.y = v1.y+v2.y;
    v.z = v1.z+v2.z;
    return v;
}

GLfloat vectDotProd(Vec3 v1, Vec3 v2)
{
    return v1.x * v2.x+
           v1.y * v2.y+
           v1.z * v2.z;
}

Vec3 vectCrossProd(Vec3 v1, Vec3 v2)
{
    Vec3 nV;
    nV.x = (v1.y * v2.z) - (v1.z * v2.y);
    nV.y = (v1.z * v2.x) - (v1.x * v2.z);
    nV.z = (v1.x * v2.y) - (v1.y * v2.x);
    return nV;
}

GLfloat vectMagnitude(Vec3 v)
{
    GLfloat length = sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
    return length;
}

Vec3 vectNormalize(Vec3 v1)
{
    GLfloat length = vectMagnitude(v1);
    v1.x /= length;
    v1.y /= length;
    v1.z /= length;
}


