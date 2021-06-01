#include "Enemy_Soldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include <math.h>
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include <math.h>
Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{
	float idleAnimSpeed = 0.05f;
	float runAminSpeed = 0.05f;
	float deathAnimSpeed = 0.05f;
	float grenadeAnimSpeed = 0.05f;

	soldierSpeed = 0.1f;
	
	
	// idle animations

	downIdleAnim.PushBack({ 115,362,26,40 });
	downIdleAnim.PushBack({ 115,362,26,40 });
	downIdleAnim.loop = true;
	downIdleAnim.speed = idleAnimSpeed;

	downRightIdleAnim.PushBack({ 115,405,26,40 });
	downRightIdleAnim.PushBack({ 115,405,26,40 });
	downRightIdleAnim.loop = true;
	downRightIdleAnim.speed = idleAnimSpeed;

	downLeftIdleAnim.PushBack({ 115,315,26,40 });
	downLeftIdleAnim.PushBack({ 115,315,26,40 });
	downLeftIdleAnim.loop = true;
	downLeftIdleAnim.speed = idleAnimSpeed;

	rightIdleAnim.PushBack({ 115,450,26,40 });
	rightIdleAnim.PushBack({ 115,450,26,40 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleAnimSpeed;

	upRightIdleAnim.PushBack({ 115,598,26,40 });
	upRightIdleAnim.PushBack({ 115,598,26,40 });
	upRightIdleAnim.loop = true;
	upRightIdleAnim.speed = idleAnimSpeed;

	upIdleAnim.PushBack({ 115,549,26,40 });
	upIdleAnim.PushBack({ 115,549,26,40 });
	upIdleAnim.loop = true;
	upIdleAnim.speed = idleAnimSpeed;

	upLeftIdleAnim.PushBack({ 115,649,26,40 });
	upLeftIdleAnim.PushBack({ 115,649,26,40 });
	upLeftIdleAnim.loop = true;
	upLeftIdleAnim.speed = idleAnimSpeed;

	leftIdleAnim.PushBack({ 115,497,26,40 });
	leftIdleAnim.PushBack({ 115,497,26,40 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = idleAnimSpeed;

	// moove animations

	downAnim.PushBack({ 115,362,26,40 });
	downAnim.PushBack({ 75,362,26,40 });
	downAnim.PushBack({ 35,362,26,40 });
	downAnim.loop = true;
	downAnim.speed = runAminSpeed;

	downRightAnim.PushBack({ 115,405,26,40 });
	downRightAnim.PushBack({ 75,405,26,40 });
	downRightAnim.PushBack({ 35,405,26,40 });
	downRightAnim.PushBack({ 7,405,26,40 });
	downRightAnim.loop = true;
	downRightAnim.speed = runAminSpeed;

	downLeftAnim.PushBack({ 115,315,26,40 });
	downLeftAnim.PushBack({ 75,315,26,40 });
	downLeftAnim.PushBack({ 35,405,26,40 });
	downLeftAnim.PushBack({ 7,405,26,40 });
	downLeftAnim.loop = true;
	downLeftAnim.speed = runAminSpeed;


	rightAnim.PushBack({ 75,450,26,40 });
	rightAnim.PushBack({ 115,405,26,40 });
	rightAnim.PushBack({ 75,405,26,40 });
	rightAnim.PushBack({ 35,405,26,40 });
	rightAnim.PushBack({ 7,405,26,40 });
	rightAnim.loop = true;
	rightAnim.speed = runAminSpeed;

	upRightAnim.PushBack({ 115,598,26,40 });
	upRightAnim.PushBack({ 75,598,26,40 });
	upRightAnim.PushBack({ 35,598,26,40 });
	upRightAnim.loop = true;
	upRightAnim.speed = runAminSpeed;

	upAnim.PushBack({ 115,549,26,40 });
	upAnim.PushBack({ 75,549,26,40 });
	upAnim.PushBack({ 35,549,26,40 });
	upAnim.loop = true;
	upAnim.speed = runAminSpeed;

	upLeftAnim.PushBack({ 115,649,26,40 });
	upLeftAnim.PushBack({ 75,649,26,40 });
	upLeftAnim.PushBack({ 35,649,26,40 });
	upLeftAnim.loop = true;
	upLeftAnim.speed = runAminSpeed;

	leftAnim.PushBack({ 75,497,26,40 });
	leftAnim.PushBack({ 115,497,26,40 });
	leftAnim.PushBack({ 75,497,26,40 });
	leftAnim.PushBack({ 35,497,26,40 });
	leftAnim.loop = true;
	leftAnim.speed = runAminSpeed;

	// grenade animation

	grenadeAnim.PushBack({ 200,317,34,43 });
	grenadeAnim.PushBack({ 243,317,34,43 });
	grenadeAnim.loop = false;
	grenadeAnim.speed = grenadeAnimSpeed;

	// Death animation

	
	//upRightDeath;	

	//upLeftDeath;
	
	//downRightDeath;
	
	//downLeftDeath;

	// Collider
	
	currentAnim = &downIdleAnim;
	collider = App->collisions->AddCollider({0, 0, 24, 40}, Collider::Type::ENEMY, (Module*)App->enemies);

	// TODO 3: Have the Brown Cookies describe a path in the screen
	/////////////////////////////////////////////////////////////
	
	playerPosition = App->player->GetPlayerPosition();	

	distanceX = 0.0f;
	distanceY = 0.0f;
	distanceXY = 0.0f;

	resultX = 0.0f;
	resultY = 0.0f;
	counter = 0;
	soldierSpeed = 0.5f;
	realDistance = 0.0f;

	timeAlive = 1000;
	inmortal = true;
	movement = MovementStage::ADVANCE;

	pushTimerReference = RandomRange(100, 300);
	pushTimer = pushTimerReference;
	path.loop = false;
	path.PushBack({ 0, 0 }, 1);

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

void Enemy_Soldier::Update()
{
	////////////////////////////////////////////////////
	path.Update();

	//playerPosition = (fPoint)App->player->position;
	playerPosition = App->player->GetPlayerPosition();
	if (pushTimer <= 0)
	{
		
		playerPosition = (fPoint)App->player->position;


		soldierDirection = fPoint{
			playerPosition.x + RandomRange(-10, 10),
			playerPosition.y + RandomRange(-10, 10)
		};

		distanceX = playerPosition.x - position.x;
		distanceY = playerPosition.y - position.y;

		distTotal = sqrtf(powf(distanceX, 2) + powf(distanceY, 2));


		switch (movement) {
		case MovementStage::ADVANCE:


			movement = MovementStage::BACKUP;
			pushTimerReference = RandomRange(20, 100);
			break;

		case MovementStage::BACKUP:

			

			movement = MovementStage::STAY;
			pushTimerReference = RandomRange(50, 200);
		
			break;

		case MovementStage::STAY:
			
			

			movement = MovementStage::ADVANCE;
			pushTimerReference = RandomRange(20, 100);
			path.PushBack({ 0, 0 }, pushTimerReference);
			break;
		}

		float speedX = (distanceX / distTotal) * soldierSpeed;
		float speedY = (distanceY / distTotal) * soldierSpeed;

		//LOG("speedX x: %f", speedX);
		LOG("speedY y: %f", speedY);

		if (movement != MovementStage::STAY && distTotal != 0) {
			relativePosition.x += speedX;
			relativePosition.y += speedY;
			path.PushBack({ speedX,speedY }, pushTimerReference);
			
			LOG("time ref: %i //////////", pushTimerReference);
		}


		pushTimer = pushTimerReference;
	}
	else {
		pushTimer--;
	}

	float speedX = (distanceX / distTotal) * soldierSpeed;
	float speedY = (distanceY / distTotal) * soldierSpeed;

	LOG("speedX x: %f", speedX);
	LOG("speedY y: %f", speedY);
	LOG("distance x: %f", distanceX);
	LOG("distance y: %f", distanceY);
	LOG("total distance: %f", distTotal);
	LOG("speed: %f", soldierSpeed);

	//if (movement != MovementStage::STAY) {
	//	
	//	float speedX = (distanceX / distTotal) * soldierSpeed;
	//	float speedY = (distanceY / distTotal) * soldierSpeed;
	//
	//	LOG("speedX x: %f", speedX);
	//	LOG("speedY y: %f", speedY);
	//	LOG("Total distance: %f", distTotal);
	//
	//	
	//
	//	if (distTotal != 0) {
	//		relativePosition.x += speedX;
	//		relativePosition.y += speedY;
	//	}
	//	
	//
	//}
	//LOG("time alive: %i", timeAlive);
	LOG("soldier x: %f, y: %f", position.x, position.y);
	LOG("timer: %i", pushTimer);
	
	
	
	//LOG("mov type: %i", movement);
	//
	//LOG("player x: %f", App->player->position.x);
	//LOG("player y: %f", App->player->position.y);
	//LOG("player x: %f", playerPosition.x);
	//LOG("player y: %f", playerPosition.y);
	//
	//LOG("soldier x: %f", position.x);
	//LOG("soldier y: %f", position.y);





	//relativePosition.x += resultX;
	//relativePosition.y += resultY;

	/*
	positionA = position;
	positionB = spawnPos + path.GetRelativePosition();
	positionC = positionB - positionA;
	distTotal = positionC.x + positionC.y;

	if (relativePosition.x > 1)  // hacer que no pase de x distancia al caminar
	{
		relativePosition.x = ((positionC.x * 100) / distTotal) * soldierSpeed;
	}

	if (relativePosition.y > 1)  // hacer que no pase de y distancia al caminar
	{
		relativePosition.y = ((positionC.y * 100) / distTotal) * soldierSpeed;
	}
	*/
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	//position.x = spawnPos.x + relativePosition.x;
	//position.x = spawnPos.y + relativePosition.y;

	//pushTimer--;
	//
	//if (pushTimer <= 0) {
	//
	//	//movement calculations
	//
	//	playerPosition = App->player->GetPlayerPosition();
	//
	//	distanceX = GetDistanceX(position.x, playerPosition.x);
	//	distanceY = GetDistanceY(position.y, playerPosition.y);
	//
	//	if (distanceY == 0.0000000f)
	//	{
	//		distanceY = 0.000001f;
	//	}
	//	if (distanceX == 0.0000000f)
	//	{
	//		distanceX = 0.000001f;
	//	}
	//
	//	distanceXY = fabs(distanceX + distanceY);
	//
	//	resultX = (distanceX / distanceXY) * soldierSpeed;                           
	//	resultY = (distanceY / distanceXY) * soldierSpeed;
	//
	//	realDistance = RealDistancePlayerEnemy(distanceX, distanceY);
	//
	//	// Animations
	//
	//	if (((resultX >= ((1/3)*soldierSpeed)) && (resultX >= ((2/ 3)*soldierSpeed))) && ((resultY >= ((1 / 3) * soldierSpeed)) && (resultY >= ((2 / 3) * soldierSpeed))))
	//	{
	//		downRightAnim.Reset();
	//		currentAnim = &downRightAnim; //diagonal down right
	//	}
	//
	//	if (((resultX >= ((-1 / 3) * soldierSpeed)) && (resultX >= ((-2 / 3) * soldierSpeed))) && ((resultY >= ((1 / 3) * soldierSpeed)) && (resultY >= ((2 / 3) * soldierSpeed))))
	//	{
	//		//diagonal down left
	//
	//		downLeftAnim.Reset();
	//		currentAnim = &downLeftAnim;
	//	}
	//	
	//	if (((resultX >= ((-1 / 3) * soldierSpeed)) && (resultX >= ((-2 / 3) * soldierSpeed))) && ((resultY >= ((-1 / 3) * soldierSpeed)) && (resultY >= ((-2 / 3) * soldierSpeed))))
	//	{
	//		//diagonal up left
	//
	//		upLeftAnim.Reset();
	//		currentAnim = &upLeftAnim;
	//	}
	//
	//	if (((resultX >= ((1 / 3) * soldierSpeed)) && (resultX >= ((2 / 3) * soldierSpeed))) && ((resultY >= ((-1 / 3) * soldierSpeed)) && (resultY >= ((-2 / 3) * soldierSpeed))))
	//	{
	//		//diagonal up right
	//
	//		upRightAnim.Reset();
	//		currentAnim = &upRightAnim;
	//	}
	//
	//	if (((resultX > ((2 / 3) * soldierSpeed)) ) && ((resultY > ((-1 / 3) * soldierSpeed)) && (resultY < ((1 / 3) * soldierSpeed))))
	//	{
	//		//  right
	//
	//		rightAnim.Reset();
	//		currentAnim = &rightAnim;
	//	}
	//
	//	if (((resultX < ((-2 / 3) * soldierSpeed))) && ((resultY > ((-1 / 3) * soldierSpeed)) && (resultY < ((1 / 3) * soldierSpeed))))
	//	{
	//		//  left
	//		leftAnim.Reset();
	//		currentAnim = &leftAnim;
	//	}
	//
	//	if (((resultY > ((2 / 3) * soldierSpeed))) && ((resultX > ((-1 / 3) * soldierSpeed)) && (resultX < ((1 / 3) * soldierSpeed))))
	//	{
	//		//  down
	//		downAnim.Reset();
	//		currentAnim = &downAnim;
	//	}
	//
	//	if (((resultY < ((-2 / 3) * soldierSpeed))) && ((resultX > ((-1 / 3) * soldierSpeed)) && (resultX < ((1 / 3) * soldierSpeed))))
	//	{
	//		//  up
	//		upAnim.Reset();
	//		currentAnim = &upAnim;
	//	}
	//	
	//
	//	// Soldier logic
	//
	//	path.PushBack({ resultX, resultY }, 1);
	//	path.PushBack({ 0.0f, 0.0f }, 1);
	//	path.PushBack({ resultX, resultY }, 1);
	//	path.PushBack({ 0.0f, 0.0f }, 1);
	//	path.PushBack({ resultX, resultY }, 1);
	//	path.PushBack({ 0.0f, 0.0f }, 1);
	//
	//	for (int i = 4; i >= 0; i--)
	//	{
	//		App->particles->AddParticle(App->particles->EnemyBullet, 1, position.x, position.y, 1, Collider::Type::ENEMY_SHOT,1);
	//		//App->audio->PlayFx(laserFx);
	//	}
	//
	//	pushTimer = pushTimerReference;
	//
	//	distanceX = 0;
	//	distanceY = 0;
	//	distanceXY = 0;
	//	resultX = 0;
	//	resultY = 0;
	//}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

float Enemy_Soldier::GetDistanceX(float enemyPosX, float playerPosX)
{
	return playerPosX - enemyPosX;

}

float Enemy_Soldier::GetDistanceY(float enemyPosY, float playerPosY)
{
	return playerPosY - enemyPosY;

}

float Enemy_Soldier::RealDistancePlayerEnemy(float x, float y)
{
	float result = 0.0f;
	float X, Y, Z;

	X = x * x;
	Y = y * y;

	Z = X + Y;

	result = sqrt(Z);

	return result;
}

int Enemy_Soldier::RandomRange(int value01, int value02) {

	if (value01 > value02) {

		int i = value01;
		value01 = value02;
		value02 = i;

	}
	return(rand() % (value02 - value01 + 1) + value01);

}
