#include <stdio.h>
#include <stdlib.h>
#include <gl/freeglut.h>
#include "GameObject.h"


void GameObjInitialize(GameObject *GameObj)
{
    GameObj->modelData = malloc(sizeof(OFFFile));

    //intialize logical centre to 0,0,0
    (*GameObj).center.x = 0;
    (*GameObj).center.y = 0;
    (*GameObj).center.z = 0;

    //initialize scale to 1
    (*GameObj).scale.x = 1;
    (*GameObj).scale.y = 1;
    (*GameObj).scale.z = 1;

    //initial offset to put center of objet at 0,0,0
    (*GameObj).offset.x = 0;
    (*GameObj).offset.y = 0;
    (*GameObj).offset.z = 0;

    GameObj->hitBox = malloc(sizeof(HitBox));
    //GameObj->hitBox->parent = GameObj;
}

//load in a 3d model
void GameObjSetModel(GameObject *GameObj,char * fileName)
{
    readOFFFile(GameObj->modelData,fileName);

    //GameObj->modelData = &nModel;
    //initialize center to 0
    (*GameObj).center.x = 0;
    (*GameObj).center.y = 0;
    (*GameObj).center.z = 0;

    //initialize scale to 1
    (*GameObj).scale.x = 1;
    (*GameObj).scale.y = 1;
    (*GameObj).scale.z = 1;

    //initial offset to put center of objet at 0,0,0
    (*GameObj).offset.x = (*GameObj).modelData->center.x * -1.0;
    (*GameObj).offset.y = (*GameObj).modelData->center.y * -1.0;
    (*GameObj).offset.z = (*GameObj).modelData->center.z * -1.0;
}

//render model with offsets,poisiton and scale accounted for
void GameObjRender(GameObject *GameObj)
{

    Vec3 pos;
    pos.x = GameObj->center.x+GameObj->offset.x;
    pos.y = GameObj->center.y+GameObj->offset.y;
    pos.z = GameObj->center.z+GameObj->offset.z;

    renderOFF(GameObj->modelData,pos,GameObj->scale);
}

//set position and translate model to new location
void GameObjSetPosition(GameObject *GameObj, GLfloat nX, GLfloat nY,GLfloat nZ)
{
    (*GameObj).center.x = nX;
    (*GameObj).center.y = nY;
    (*GameObj).center.z = nZ;
}


//transform the object in worldspace
void GameObjTransform(GameObject *GameObj, GLfloat nX, GLfloat nY,GLfloat nZ)
{
    //(*GameObj).offset[0] += nX;
    //(*GameObj).offset[1] += nY;
    //(*GameObj).offset[2] += nZ;

    (*GameObj).center.x += nX;
    (*GameObj).center.y += nY;
    (*GameObj).center.z += nZ;

}

//rotate the object in worldspace
void GameObjRotate(GameObject *GameObj, GLfloat rX, GLfloat rY,GLfloat rZ, GLfloat deg);

//scale the object
void GameObjScale(GameObject *GameObj, GLfloat sX, GLfloat sY,GLfloat sZ);

//print all info of game object
void GameObjPrintInfo(GameObject *GameObj){
    printf("%s Data:\n",GameObj->name);
    printf("Center: (%f %f %f)\n",GameObj->center.x,GameObj->center.y,GameObj->center.z);
    printf("Offset: (%f %f %f)\n,",GameObj->offset.x,GameObj->offset.y,GameObj->offset.z);
    printOFFInfo(GameObj->modelData);

}
