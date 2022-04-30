#pragma once

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "GameObject.h"
#include "HitBox.h"

typedef struct {
	HitBox* hit;
	GameObject* gameObj;
}Collision;

#endif // PHYSICS_H_INCLUDED
