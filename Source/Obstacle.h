//#pragma once
#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include "p2Point.h"
#include "Animation.h"


struct Collider;

class Obstacle {
public:

	Obstacle();

	Obstacle(const Obstacle& p);

	~Obstacle();

	bool Update();

public:

	iPoint position;

	Animation anim;

	bool isAlive = false;

	int life;

	int frameCount = 0;

	Collider* collider = nullptr;

	//friend OnCollision(Collider* c1, Collider* c2) ;
};


#endif 


