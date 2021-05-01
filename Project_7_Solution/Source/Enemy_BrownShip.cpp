#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{
	float idleAnimSpeed = 0.01f;
	float runAminSpeed = 0.01f;
	float shootAnimSpeed = 0.01f;
	float grenadeAnimSpeed = 0.01f;

	downIdleAnim.PushBack({0,0,210,220});
	downIdleAnim.PushBack({ 5,72,21,22 });
	downIdleAnim.loop = true;
	downIdleAnim.speed = idleAnimSpeed;

	
	currentAnim = &downIdleAnim;
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);

	// TODO 3: Have the Brown Cookies describe a path in the screen
	/////////////////////////////////////////////////////////////
	float distanceX = GetDistanceX(position.x, App->player->position.x);
	float distanceY = GetDistanceY(position.y, App->player->position.y);



	path.PushBack({-1.0f, -0.5f}, 100); // x movement, y movement, frames de
	path.PushBack({-1.0f, 0.5f}, 100);
	path.PushBack({-1.0f, 1.0f}, 100);	
	
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
