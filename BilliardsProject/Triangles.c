#include "Triangles.h"

GLfloat triangleArea(point3D p1, point3D p2, point3D p3)
{
    vect3D vect1 = vectMinus(p1, p2);
    vect3D vect2 = vectMinus(p1, p3);
    vect3D vect3 = vectCrossProd(vect1, vect2);
    GLfloat area = vectMagnitude(vect3);
    area /= 2;
    return area;
}

//not tested
vect3D triangleNormal(point3D p1, point3D p2, point3D p3)
{
    vect3D vect1 = vectMinus(p1, p2);
    vect3D vect2 = vectMinus(p1, p3);

    return vectCrossProd(vect1, vect2);
}

//not tested
vect3D triangleUnitNormal(point3D p1, point3D p2, point3D p3)
{
    vect3D v = triangleNormal(p1, p2, p3);
    v = vectNormalize(v);
    return v;
}