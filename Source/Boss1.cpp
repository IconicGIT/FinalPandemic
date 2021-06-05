#include "Boss1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include <math.h>
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include <time.h>

#include <math.h>
Enemy_Boss01::Enemy_Boss01(int x, int y) : Enemy(x, y)
{
	float AnimSpeed = 0.05f;
	
	BossIdleAnim.PushBack({ 0,0,128,158 });

	BossShootingAnim.PushBack({ 0,0,128,158 });
	BossShootingAnim.PushBack({ 128,0,128,158 });
	BossShootingAnim.PushBack({ 0,0,128,158 });
	BossShootingAnim.PushBack({ 256,0,128,158 });
	BossShootingAnim.loop = true;
	BossShootingAnim.speed = 0.3f;

	// Death animation



	// Collider

	currentAnim = &BossIdleAnim;
	collider = App->collisions->AddCollider({ 0, 0, 24, 40 }, Collider::Type::ENEMY, (Module*)App->enemies);

	// TODO 3: Have the Brown Cookies describe a path in the screen
	/////////////////////////////////////////////////////////////


	timeAlive = 1000;
	inmortal = true;
	movement = MovementStage::ENTRANCE;

	pivot = { 1050,50 };
	pushTimerReference = 5*50 + 30;
	pushTimer = pushTimerReference;
	path.loop = false;
	path.PushBack({ 0,0.3f }, 1);
	shootWhileMoving = false;
	
	srand(time(0));

	//sqrt(pow(distanceXY,2))
	//path.PushBack({-1.0f, -0.5f}, 100); // x movement, y movement, frames de
	//path.PushBack({0.0f, 0.0f}, 100);

	//
	//playerPosition = App->player->GetPlayerPosition();
	//
	//distanceX = GetDistanceX(position.x, playerPosition.x);
	//distanceY = GetDistanceY(position.y, playerPosition.y);
	//
	//if (distanceY == 0.0000000f)
	//{
	//	distanceY = 0.000001f;
	//}
	//if(distanceX == 0.0000000f)
	//{
	//	distanceX = 0.000001f;
	//}
	//
	//distanceXY = fabs(distanceX + distanceY);
	//
	//resultX = (distanceX / distanceXY)*1;                            // It updates? but does the player position update?
	//resultY = (distanceY / distanceXY)*1;
	//
	//realDistance = RealDistancePlayerEnemy(distanceX, distanceY);
	/////
	//if (counter == 0)
	//{
	//	path.PushBack({ 0.0f, 0.0f }, 100);
	//}
	//
	//path.PushBack({ resultX, resultY }, 100);	
	//path.PushBack({ 0.0f, 0.0f }, 10);

	//for (int i = 4; i >= 0; i--)
	//{
	//	App->particles->AddPreciseParticle(App->particles->EnemyBullet, 0, position.x, position.y, , Collider::Type::ENEMY_SHOT);
	//	App->audio->PlayFx(laserFx);
	//}

	counter++;
}

void Enemy_Boss01::Update()
{
	////////////////////////////////////////////////////
	path.Update();

	//playerPosition = (fPoint)App->player->position;
	
	float pushX;
	float pushY;

	fPoint movementRangeX;
	fPoint movementRangeY;

	if (pushTimer <= 0)
	{

		switch (movement) {
		case MovementStage::ENTRANCE:
			pushTimerReference = 2 * 60;
			
			path.PushBack({ 0, 0 }, pushTimerReference);
			currentAnim = &BossIdleAnim;
			
			shootWhileMoving = (bool)iRandomRange(0, 1);
			movement = MovementStage::MOVE;
			break;

		case MovementStage::MOVE:
			pushTimerReference = 60;
			if (shootWhileMoving) {
				currentAnim = &BossShootingAnim;

				//shoot
			}
			else {
				currentAnim = &BossIdleAnim;
			}
			
			movementRangeX = { 0.2f,0.7f };
			movementRangeY = { 0.2f,0.5f };

			if (position.x < pivot.x) {
				pushX = fRandomRange(movementRangeX.x, movementRangeX.y);
				LOG("moving right")
			}
			if (position.x > pivot.x) {
				pushX = -fRandomRange(movementRangeX.x, movementRangeX.y);
				LOG("moving left")
			}
			if (position.y < pivot.y) {
				pushY = fRandomRange(movementRangeY.x, movementRangeY.y);
				LOG("moving down")
			}
			if (position.y > pivot.y) {
				pushY = -fRandomRange(movementRangeY.x, movementRangeY.y);
				LOG("moving up")
			}

			path.PushBack({ pushX,pushY }, pushTimerReference);
			movement = MovementStage::SHOOT;
			break;

		case MovementStage::SHOOT:
			path.Reset();
			BossIdleAnim.Reset();
			currentAnim = &BossShootingAnim;


			pushTimerReference = 60;


			if (!shootWhileMoving) shootWhileMoving = (bool)iRandomRange(0, 1);
			else shootWhileMoving = false;

			path.PushBack({ 0,0 }, pushTimerReference);
			movement = MovementStage::MOVE;
			break;
		}

		

		pushTimer = pushTimerReference;
	}
	else {
		pushTimer--;
	}

	//LOG(" x: %f, y: %f", position.x, position.y);
	
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}



int Enemy_Boss01::iRandomRange(int value01, int value02) {

	if (value01 > value02) {

		int i = value01;
		value01 = value02;
		value02 = i;

	}
	return(rand() % (value02 - value01 + 1) + value01);

}

float Enemy_Boss01::fRandomRange(float value01, float value02) {

	if (value01 > value02) {

		float i = value01;
		value01 = value02;
		value02 = i;

	}
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = value02 - value01;
	float r = random * diff;
	return value01 + r;

}