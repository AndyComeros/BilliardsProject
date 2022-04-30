#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

#include <gl/freeglut.h>
#include "Triangles.h"
//#include "GameObject.h"

/**
* @brief struct holding hitbox data and reference to parent
* Game object
*
*/
typedef struct HitBox HitBox;

struct HitBox {
    //GameObject* parent;
    struct HitBox *lastHit;
    int hitBoxType;//0 if sphere 1 if AABB
    GLfloat Radius;
    GLfloat minX,maxX;
    GLfloat minY,maxY;
    GLfloat minZ,maxZ;
};

/**
* @brief determines if two hitboxes intersect
* determines which hitbox type and calls appropriate function
*
* @param h1 - first hitbox
* @param h2 - second hitbox
*
* @return int - 0 if not colliding 1 if colliding, -1 if there is an error
*/
int HitBoxIsColliding(HitBox *h1, HitBox *h2);
/**
* @brief determines if two sphere hitboxes intersect
*
* @param h1 - first hitbox
* @param h2 - second hitbox
*
* @return int - 0 if not colliding 1 if colliding, -1 if there is an error
*/
int HitSphereSphere(HitBox *h1, HitBox *h2);
int HitSphereBox(HitBox *h1, HitBox *h2);
int HitBoxBox(HitBox *h1, HitBox *h2);

//helper function
vect3D AABBClosestPoint(HitBox *boundBox, point3D point);
#endif // HITBOX_H_INCLUDED
