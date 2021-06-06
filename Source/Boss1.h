#ifndef __ENEMY_BOSS1_H__
#define __ENEMY_BOSS1_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Boss01 : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Boss01(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	int iRandomRange(int value01, int values02);
	float fRandomRange(float value01, float values02);
	void OnCollision(Collider* collider);
	void Draw();

	fPoint playerPosition;
	SDL_Rect lifeBar;

	int   counter;

	float realDistance;

	int pushTimerReference = 1;
	int pushTimer = 0;
	

	int shootTimerReference;
	int shootTimer;

	int particleTimerReference;
	int particleTimer;

	iPoint pivot;
	
	uint bossShotFX = 0;
	
	int shootWhileMoving = false;

	float bobbingAmplitude;
	float a;

	enum MovementStage
	{
		MOVE = 0,
		SHOOT = 1,
		ENTRANCE = 2,
		DEFEATED = 3

	};

	int movement;



private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	fPoint relativePosition = fPoint(0.0f, 0.0f);
	Animation BossIdleAnim;
	Animation BossShootingAnim;


	
	uint explosionFx = 0;
};

#endif // __ENEMY_BROWNSHIP_H__