#include <stdio.h>
#include <stdlib.h>
#include <gl/freeglut.h>
#include "ObjectFileLib.h"
#include "GameObject.h"


void GameObjInitialize(struct GameObject *GameObj)
{
    GameObj->modelData = malloc(sizeof(struct OFFFile));

    //intialize logical centre to 0,0,0
    (*GameObj).center[0] = 0;
    (*GameObj).center[1] = 0;
    (*GameObj).center[2] = 0;

    //initialize scale to 1
    (*GameObj).scale[0] = 1;
    (*GameObj).scale[1] = 1;
    (*GameObj).scale[2] = 1;

    //initial offset to put center of objet at 0,0,0
    (*GameObj).offset[0] = 0;
    (*GameObj).offset[1] = 0;
    (*GameObj).offset[2] = 0;

    GameObj->hitBox = malloc(sizeof(struct HitBox));
    GameObj->hitBox->parent = GameObj;
}

//load in a 3d model
void GameObjSetModel(struct GameObject * GameObj,char * fileName)
{
    readOFFFile(GameObj->modelData,fileName);

    //GameObj->modelData = &nModel;
    //initialize center to 0
    (*GameObj).center[0] = 0;
    (*GameObj).center[1] = 0;
    (*GameObj).center[2] = 0;

    //initialize scale to 1
    (*GameObj).scale[0] = 1;
    (*GameObj).scale[1] = 1;
    (*GameObj).scale[2] = 1;

    //initial offset to put center of objet at 0,0,0
    (*GameObj).offset[0] = (*GameObj).modelData->center[0] * -1.0;
    (*GameObj).offset[1] = (*GameObj).modelData->center[1] * -1.0;
    (*GameObj).offset[2] = (*GameObj).modelData->center[2] * -1.0;
}

//render model with offsets,poisiton and scale accounted for
void GameObjRender(struct GameObject * GameObj)
{

    point3D pos;
    pos[0] = GameObj->center[0]+GameObj->offset[0];
    pos[1] = GameObj->center[1]+GameObj->offset[1];
    pos[2] = GameObj->center[2]+GameObj->offset[2];

    renderOFF(GameObj->modelData,pos,GameObj->scale);
}

//set position and translate model to new location
void GameObjSetPosition(struct GameObject * GameObj, GLfloat nX, GLfloat nY,GLfloat nZ)
{
    (*GameObj).center[0] = nX;
    (*GameObj).center[1] = nY;
    (*GameObj).center[2] = nZ;
}


//transform the object in worldspace
void GameObjTransform(struct GameObject * GameObj, GLfloat nX, GLfloat nY,GLfloat nZ)
{
    //(*GameObj).offset[0] += nX;
    //(*GameObj).offset[1] += nY;
    //(*GameObj).offset[2] += nZ;

    (*GameObj).center[0] += nX;
    (*GameObj).center[1] += nY;
    (*GameObj).center[2] += nZ;

}

//rotate the object in worldspace
void GameObjRotate(struct GameObject * GameObj, GLfloat rX, GLfloat rY,GLfloat rZ, GLfloat deg);

//scale the object
void GameObjScale(struct GameObject * GameObj, GLfloat sX, GLfloat sY,GLfloat sZ);

//print all info of game object
void GameObjPrintInfo(struct GameObject * GameObj){
    printf("%s Data:\n",GameObj->name);
    printf("Center: (%f %f %f)\n",GameObj->center[0],GameObj->center[1],GameObj->center[2]);
    printf("Offset: (%f %f %f)\n,",GameObj->offset[0],GameObj->offset[1],GameObj->offset[2]);
    printOFFInfo(GameObj->modelData);

}
