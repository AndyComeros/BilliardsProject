#include "Triangles.h"

GLfloat triangleArea(point3D p1, point3D p2, point3D p3)
{
    Vec3 vect1 = vectMinus(p1, p2);
    Vec3 vect2 = vectMinus(p1, p3);
    Vec3 vect3 = vectCrossProd(vect1, vect2);
    GLfloat area = vectMagnitude(vect3);
    area /= 2;
    return area;
}

//not tested
Vec3 triangleNormal(point3D p1, point3D p2, point3D p3)
{
    Vec3 vect1 = vectMinus(p1, p2);
    Vec3 vect2 = vectMinus(p1, p3);

    return vectCrossProd(vect1, vect2);
}

//not tested
Vec3 triangleUnitNormal(point3D p1, point3D p2, point3D p3)
{
    Vec3 v = triangleNormal(p1, p2, p3);
    v = vectNormalize(v);
    return v;
}