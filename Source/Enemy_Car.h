#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"

class Enemy_Car : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Car(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;


private:
	

	// The enemy animation
	//Animation flyAnim;

	Animation carDirectionRect[16];

	int direction = 0;

};

#endif // __ENEMY_REDBIRD_H__