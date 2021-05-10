#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include "p2Point.h"


struct Collider;

class Power_Up{
public:

	Power_Up() { };

	Power_Up(const Power_Up& p) 
	{ 
	};

	~Power_Up(){ };

	bool Update();

public:

	
	iPoint position;

	

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
