//#pragma once
#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include "p2Point.h"
#include "Animation.h"


struct Collider;

class PowerUp {
public:

	PowerUp();

	PowerUp(const PowerUp& p);

	~PowerUp();

	bool Update();

public:

	iPoint position;

	Animation anim;

	bool isAlive = false;

	int id;

	int frameCount = 0;

	uint lifetime = 0;

	Collider* collider = nullptr;

	int counter;
	float _speedy;
	float _speedx;
};


#endif 

