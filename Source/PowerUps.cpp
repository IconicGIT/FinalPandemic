#include "PowerUps.h"

#include "Collider.h"
#include "Enemy_Soldier.h"
#include "Application.h"

PowerUp::PowerUp()
{
	position.SetToZero();
	id = 0;
}

PowerUp::PowerUp(const PowerUp& p) : anim(p.anim), position(p.position),
frameCount(p.frameCount), lifetime(p.lifetime), id(p.id)
{

}

PowerUp::~PowerUp()
{
	if (collider != nullptr)
	{
		collider->pendingToDelete = true;
	}

}

bool PowerUp::Update()
{
	bool ret = true;
	frameCount++;

	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}

		else if (anim.HasFinished())
			ret = false;

		

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}