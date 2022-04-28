#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "ObjectFileLib.h"
#include "HitBox.h"
#include "VectorMath.h"

//---Data---//
struct GameObject
{
    char name[20];

    OFFFile * modelData;
    HitBox * hitBox;

    //position data
    point3D center;
    GLfloat scale[3];
    GLfloat rotation[3];
    vect3D offset;//offsets transformations so center of object is center of model.

    //physics data
    vect3D velocity;
    GLfloat mass;

};
typedef struct GameObject GameObject;


//---functions---//
//initialize game object memory...
void GameObjInitialize(struct GameObject * GameObj);
//load in a 3d model
void GameObjSetModel(struct GameObject * GameObj,char * fileName);

//redner in model with offsets and scale accounted for
void GameObjRender(struct GameObject * GameObj);

//set position and translate model to new location
void GameObjSetPosition(struct GameObject * GameObj, GLfloat nX, GLfloat nY,GLfloat nZ);

//transform the object in worldspace
void GameObjTransform(struct GameObject * GameObj, GLfloat nX, GLfloat nY,GLfloat nZ);

//rotate the object in worldspace
void GameObjRotate(struct GameObject * GameObj, GLfloat rX, GLfloat rY,GLfloat rZ, GLfloat deg);

//scale the object
void GameObjScale(struct GameObject * GameObj, GLfloat sX, GLfloat sY,GLfloat sZ);

//prints info of game obj
void GameObjPrintInfo(struct GameObject * GameObj);

#endif // GAMEOBJECT_H_INCLUDED
