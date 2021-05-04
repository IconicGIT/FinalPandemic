#include "p2Point.h"
#include "PowerUps.h"
#include "Collider.h"

Power_Up::Power_Up() 
{
	position.SetToZero();
};

Power_Up::Power_Up(const Power_Up& p) : position(p.position), frameCount(p.frameCount), lifetime(p.lifetime)
{
};

Power_Up::~Power_Up()
{
	if (collider != nullptr)
	{
		collider->pendingToDelete = true;
	}		
}

bool Power_Up::Update()
{
	if ()
	{

	}
}

