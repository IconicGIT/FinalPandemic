#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include "p2Point.h"
#include "Animation.h"


struct Collider;

class PowerUp{
public:

	PowerUp() { };

	PowerUp(const PowerUp& p) 
	{ 
	};

	~PowerUp(){ };

	bool Update();

public:

	
	iPoint position;

	Animation anim;

	bool isAlive = false;

	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	uint lifetime = 0;

	// The particle's collider
	Collider* collider = nullptr;

	int counter;
	float _speedy;
	float _speedx;
};


#endif 
