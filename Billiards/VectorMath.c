
#include <gl/freeglut.h>
#include "VectorMath.h"
#include "math.h"

#include<stdio.h>
//using namespace std;

//gets vector between two points. form p1 to p2
void vectFromPoints(vect3D  v,point3D p1, point3D p2)
{
    v[0] =  (p1[0] - p2[0]);
    v[1] =  (p1[1] - p2[1]);
    v[2] =  (p1[2] - p2[2]);

}
void vectMultScalar(vect3D * v, GLfloat s)
{
    (*v)[0] *= s;
    (*v)[1] *= s;
    (*v)[2] *= s;
}
void vectMultScalars(vect3D * v, GLfloat sx,GLfloat sy,GLfloat sz)
{
    (*v)[0] *= sx;
    (*v)[1] *= sy;
    (*v)[2] *= sz;
}

void vectAddScalar(vect3D * v, GLfloat s)
{
    (*v)[0] += s;
    (*v)[1] += s;
    (*v)[2] += s;
}
void vectAddScalars(vect3D * v, GLfloat ax,GLfloat ay,GLfloat az)
{
    (*v)[0] *= ax;
    (*v)[1] *= ay;
    (*v)[2] *= az;
}

void vectAddVect(vect3D * v1, vect3D v2)
{
    (*v1)[0] += v2[0];
    (*v1)[1] += v2[1];
    (*v1)[2] += v2[2];
}

GLfloat vectDotProd(vect3D v1, vect3D v2)
{
    return v1[0] * v2[0]+
           v1[1] * v2[1]+
           v1[2] * v2[2];
}

void vectCrossProd(vect3D * v1, vect3D v2)
{
    vect3D nV;
    nV[0] = ((*v1)[1]*(v2)[2]) - ((*v1)[2]*(v2)[1]);
    nV[1] = ((*v1)[2]*(v2)[0]) - ((*v1)[0]*(v2)[2]);
    nV[2] = ((*v1)[0]*(v2)[1]) - ((*v1)[1]*(v2)[0]);

    (*v1)[0] = nV[0];
    (*v1)[1] = nV[1];
    (*v1)[2] = nV[2];
}

GLfloat vectMagnitude(vect3D v)
{
    GLfloat length = sqrt((v[0]*v[0]) + (v[1]*v[1]) + (v[2]*v[2]));
    return length;
}

void vectNormalize(vect3D * v1)
{
    GLfloat length = vectMagnitude(*v1);
    (*v1)[0] /= length;
    (*v1)[1] /= length;
    (*v1)[2] /= length;
}

GLfloat triangleArea(point3D p1, point3D p2,point3D p3)
{
    vect3D vect1;
    vectFromPoints(vect1,p1,p2);
    vect3D vect2;
    vectFromPoints(vect2,p1,p3);
    vectCrossProd(vect1,vect2);

    GLfloat area = vectMagnitude(vect1);
    area /= 2;
    return area;

}

//not tested
void triangleNormal(vect3D * v,point3D p1, point3D p2,point3D p3)
{
    vect3D vect1;
    vectFromPoints(vect1,p1,p2);
    vect3D vect2;
    vectFromPoints(vect2,p1,p3);
    vectCrossProd(vect1,vect2);

    (*v)[0] = vect1[0];
    (*v)[1] = vect1[1];
    (*v)[2] = vect1[2];
}

//not tested
void triangleUnitNormal(vect3D *  v,point3D p1, point3D p2,point3D p3)
{
    triangleNormal(v,p1,p2,p3);
    vectNormalize(v);
}
