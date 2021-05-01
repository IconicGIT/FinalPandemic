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

	float GetDistanceX(float enemyPosX, float playerPosX)
	{
		return playerPosX - enemyPosX;
	}

	float GetDistanceY(float enemyPosY, float playerPosY)
	{
		return playerPosY - enemyPosY;
	}

	float RealDistancePlayerEnemy(float x, float y)
	{
		float result = 0.0f;
		float X, Y, Z;

		X = x * x;
		Y = y * y;

		Z = X + Y;

		result = sqrt(Z);

		return result;
	}

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
	
};

#endif // __ENEMY_BROWNSHIP_H__