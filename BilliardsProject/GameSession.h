#pragma once

#ifndef GAMESESSION_H_INCLUDED
#define GAMESESSION_H_INCLUDED

#include "Physics.h"
#include "Object.h"

void initGameSession();
void gameStartingSetup();

void animateGameObjects(float deltaTime);

//temp
void testObjBody(Object* obj, int index);

void randObjBody(Object* obj);
void rotateObjects(Object* obj);

void drawBallObjects();

void resetWhiteBall();

#endif // !GAMESESSION_H_INCLUDED
