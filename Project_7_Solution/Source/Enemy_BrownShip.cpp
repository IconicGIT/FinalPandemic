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
	
	fPoint playerPosiytion = App->player->GetPlayerPosition();
	

	float distanceX = 0.0f;
	float distanceY = 0.0f;
	float distanceXY = 0.0f;

	float resultX = 0.0f;
	float resultY = 0.0f;

	//sqrt(pow(distanceXY,2))
	//path.PushBack({-1.0f, -0.5f}, 100); // x movement, y movement, frames de
	//path.PushBack({0.0f, 0.0f}, 100);


	distanceX = GetDistanceX(position.x, playerPosiytion.x);
	distanceY = GetDistanceY(position.y, playerPosiytion.y);
	distanceXY = fabs(distanceX + distanceY);

	resultX = (distanceX / distanceXY);
	resultY = (distanceY / distanceXY);

	////////////////////////////////////////////////////////////////
	path.PushBack({ resultX, resultY }, 100);
	path.PushBack({ resultX, resultY }, 100);
	path.PushBack({ 0.0f, 0.0f }, 100);
	for (int i = 4; i >= 0; i--)
	{
		App->particles->AddParticle(App->particles->EnemyBullet, 0, position.x, position.y, 1, Collider::Type::ENEMY_SHOT);
		App->audio->PlayFx(laserFx);
	}
	path.PushBack({ 0.0f, 0.0f }, 100);
	path.PushBack({ -resultX, -resultY }, 100);
	path.PushBack({ -resultX, -resultY }, 100);
	path.PushBack({ 0.0f, 0.0f }, 100);
	for (int i = 4; i >= 0; i--)
	{
		App->particles->AddParticle(App->particles->EnemyBullet, 0, position.x, position.y, 1, Collider::Type::ENEMY_SHOT);
		App->audio->PlayFx(laserFx);
	}
	path.PushBack({ 0.0f, 0.0f }, 100);


	

}

void Enemy_Soldier::Update()
{
	////////////////////////////////////////////////////
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
