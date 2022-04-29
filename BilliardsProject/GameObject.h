#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "OFFFILE.h"
#include "HitBox.h"
#include "Vector.h"
#include "Triangles.h"

//---Data---//
typedef struct {
    char name[20];

    OFFFile *modelData;
    HitBox *hitBox;

    //position data
    point3D center;
    vect3D scale;
    vect3D rotation;
    vect3D offset;//offsets transformations so center of object is center of model.

    //physics data
    vect3D velocity;
    GLfloat mass;

}GameObject;


//---functions---//
//initialize game object memory...
void GameObjInitialize(GameObject *GameObj);
//load in a 3d model
void GameObjSetModel(GameObject *GameObj,char * fileName);

//redner in model with offsets and scale accounted for
void GameObjRender(GameObject *GameObj);

//set position and translate model to new location
void GameObjSetPosition(GameObject *GameObj, GLfloat nX, GLfloat nY,GLfloat nZ);

//transform the object in worldspace
void GameObjTransform(GameObject *GameObj, GLfloat nX, GLfloat nY,GLfloat nZ);

//rotate the object in worldspace
void GameObjRotate(GameObject *GameObj, GLfloat rX, GLfloat rY,GLfloat rZ, GLfloat deg);

//scale the object
void GameObjScale(GameObject *GameObj, GLfloat sX, GLfloat sY,GLfloat sZ);

//prints info of game obj
void GameObjPrintInfo(GameObject *GameObj);

#endif // GAMEOBJECT_H_INCLUDED
