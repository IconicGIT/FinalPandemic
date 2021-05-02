#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include <math.h>
#include "ModuleParticles.h"
#include "ModuleAudio.h"

Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{
	float idleAnimSpeed = 0.01f;
	float runAminSpeed = 0.01f;
	float shootAnimSpeed = 0.01f;
	float grenadeAnimSpeed = 0.01f;

	downIdleAnim.PushBack({ 5,72,21,22});
	downIdleAnim.PushBack({ 5,100,21,22 });
	downIdleAnim.loop = true;
	downIdleAnim.speed = idleAnimSpeed;

	
	currentAnim = &downIdleAnim;
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);

	// TODO 3: Have the Brown Cookies describe a path in the screen
	/////////////////////////////////////////////////////////////
	
	playerPosition = App->player->GetPlayerPosition();	

	distanceX = 0.0f;
	distanceY = 0.0f;
	distanceXY = 0.0f;

	resultX = 0.0f;
	resultY = 0.0f;
	counter = 0;

	realDistance = 0.0f;

	timeAlive = 1000;
	inmortal = true;

	pushTimerReference = 200.0f;
	pushTimer = pushTimerReference;

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
	position = spawnPos + path.GetRelativePosition();


	pushTimer--;
	if (pushTimer <= 0) {

		playerPosition = App->player->GetPlayerPosition();

		distanceX = GetDistanceX(position.x, playerPosition.x);
		distanceY = GetDistanceY(position.y, playerPosition.y);

		if (distanceY == 0.0000000f)
		{
			distanceY = 0.000001f;
		}
		if (distanceX == 0.0000000f)
		{
			distanceX = 0.000001f;
		}

		distanceXY = fabs(distanceX + distanceY);

		resultX = (distanceX / distanceXY) * 1;                            // It updates? but does the player position update?
		resultY = (distanceY / distanceXY) * 1;

		realDistance = RealDistancePlayerEnemy(distanceX, distanceY);
		///
		//if (counter == 0)
		//{
		//	path.PushBack({ 0.0f, 0.0f }, 100);
		//}

		path.PushBack({ resultX, resultY }, 100);
		path.PushBack({ 0.0f, 0.0f }, 100);

		for (int i = 4; i >= 0; i--)
		{
			App->particles->AddParticle(App->particles->EnemyBullet, 1, position.x, position.y, 1, Collider::Type::ENEMY_SHOT,1);
			App->audio->PlayFx(laserFx);
		}

		pushTimer = pushTimerReference;

		distanceX = 0;
		distanceY = 0;
		distanceXY = 0;
		resultX = 0;
		resultY = 0;
	}

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
