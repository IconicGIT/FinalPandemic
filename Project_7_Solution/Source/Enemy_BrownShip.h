#ifndef __ENEMY_SOLDIER_H__
#define __ENEMY_SOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Soldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Soldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	float GetDistanceX(float enemyPosX, float playerPosX);

	float GetDistanceY(float enemyPosY, float playerPosY);

	float RealDistancePlayerEnemy(float x, float y);

	fPoint playerPosition;

	float distanceX;
	float distanceY;
	float distanceXY;

	float resultX;
	float resultY;
	int   counter;

	float realDistance;

	float pushTimer = 0;
	float pushTimerReference = 400;

	

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies

	// Shoot / Idle Animations 
	Animation upIdleAnim;
	Animation upRightIdleAnim;
	Animation rightIdleAnim;
	Animation downRightIdleAnim;
	Animation downIdleAnim;
	Animation downLeftIdleAnim;
	Animation upLeftIdleAnim;
	Animation leftIdleAnim;

	// Move Animations
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;
	Animation downRightAnim;
	Animation upRightAnim;
	Animation downLeftAnim;
	Animation upLeftAnim;

	// Death Animation
	Animation upRightDeath;
	Animation upLeftDeath;
	Animation downRightDeath;
	Animation downLeftDeath;
	

	uint laserFx = 0;
	uint explosionFx = 0;
};

#endif // __ENEMY_BROWNSHIP_H__