#pragma once

#ifndef GAMESESSION_H_INCLUDED
#define GAMESESSION_H_INCLUDED

#include "Physics.h"
#include "Object.h"
	/**
	*	@brief initializes the billiards game session balls with default positions,
	*	physics properties and lighting materials.
	*	@return void
	*/
void initGameSession();
void gameStartingSetup();
	/**
	*	@brief runs a physics update on all the games Cues balls, checks if they are colliding.
	*	@param deltaTime - time since last update
	*	@return void
	*/
void animateGameObjects(float deltaTime);
	/**
	*	@brief sets inital position and properties of a ball based on an integer value
	*	@param obj - object being initialized
	*	@param index - index of object being initailized
	*	@return void
	*/
void testObjBody(Object* obj, int index);
	/**
	*	@brief render function for all the sphere objects in the scene
	*	@return void
	*/
void drawBallObjects();
	/**
	*	@brief Resets the cue balls properties
	*	@return void
	*/
void resetWhiteBall();

#endif // !GAMESESSION_H_INCLUDED
