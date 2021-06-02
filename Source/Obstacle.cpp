
#include "Obstacle.h"

#include "Collider.h"
#include "Enemy_Soldier.h"
#include "Application.h"

Obstacle::Obstacle()
{
	position.SetToZero();
}

Obstacle::Obstacle(const Obstacle& o) : anim(o.anim), position(o.position),
frameCount(o.frameCount), life(o.life)
{

}

Obstacle::~Obstacle()
{
	if (collider != nullptr)
	{
		collider->pendingToDelete = true;
	}

}

bool Obstacle::Update()
{
	bool ret = true;
	frameCount++;

	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		if (life > 0)
		{
		             // Posible error
			ret = false;
		}

		else if (anim.HasFinished())
			ret = false;



		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}
