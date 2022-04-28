#include "VectorMath.h"
#include "ObjectFileLib.h"
#include "GameObject.h"

typedef struct HitBox HitBox;//dont know why its needed when ive already typedefed but k

//generic hit detection funciton.
int HitBoxIsColliding(HitBox * h1,HitBox * h2)
{
    int hitType = h1->hitBoxType + h2->hitBoxType;

    switch(hitType)
    {
    case 0:
        return HitSphereSphere(h1,h2);
        break;
    case 1:
        return HitSphereBox(h1,h2);
        break;
    case 2:
        break;
    }
    return -1;
}

//check if shere hitboxes collide
int HitSphereSphere(HitBox * h1, HitBox * h2)
{
    vect3D vect1;
    vectFromPoints(vect1,h1->parent->center,h2->parent->center);
    GLfloat mag = vectMagnitude(vect1);

    if(mag <= (h1->Radius + h2->Radius))
    {
        if(h1->lastHit != h2)
        {
            h1->lastHit = h2;
            h2->lastHit = h1;
            return 1;
        }
        return 0;
    }
    else
    {
        h1->lastHit = NULL;
        h2->lastHit = NULL;
        return 0;
    }
}

//if sphere collides with box
int HitSphereBox(HitBox * h1, HitBox * h2)
{
    HitBox * sphere;
    HitBox * box;

    //determine which is sphere and box
    if(h1->hitBoxType == 0)
    {
        sphere = h1;
        box = h2;
    }
    else
    {
        box = h1;
        sphere = h2;
    }

    point3D closePoint;
    vect3D difVect;//vect between the 2 points
    GLfloat distance;

    AABBClosestPoint(&closePoint,box,sphere->parent->center);
    vectFromPoints(&difVect, sphere->parent->center,closePoint);

    distance = vectMagnitude(difVect);

    if(distance < sphere->Radius)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int HitBoxBox(HitBox * h1, HitBox * h2)
{
    return 0;
}

//returns closest point on a AABB to a point- NOT TESTED
void AABBClosestPoint(point3D * result,HitBox * boundBox,point3D point)
{
    for(int i=0; i<3; i++)
    {
        if(point[i] > boundBox->maxX)
        {
            *result[i] = boundBox->maxX;
        }
        else if(point[i] < boundBox->maxX)
        {
            *result[i] = boundBox->minX;
        }
        else
        {
            *result[i] = point[i];
        }
    }
}
