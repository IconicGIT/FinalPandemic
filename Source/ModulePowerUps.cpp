#include "ModulePowerUps.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"

#include "SDL/include/SDL_timer.h"

ModulePowerUps::ModulePowerUps(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
		powerUps[i] = nullptr;
}

ModulePowerUps::~ModulePowerUps()
{

}

bool ModulePowerUps::Start()
{
	LOG("Loading Power Ups");
	texture = App->textures->Load("Assets/Sprites/items_and_particles.png");

	Medal1.anim.PushBack({ 274, 296, 33, 30 }); // TODO
	Medal1.anim.loop = true;
	Medal1.anim.speed = 1.0f;
	Medal1.lifetime = 300;
	 
	MachineGun.anim.PushBack({ 274, 296, 33, 30 }); // TODO
	MachineGun.anim.loop = true;
	MachineGun.anim.speed = 1.0f;
	MachineGun.lifetime = 300;

	return true;
}



bool ModulePowerUps::CleanUp()
{
	LOG("Unloading power ups");

	// Delete all remaining active power ups on application exit
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
	{
		if (powerUps[i] != nullptr)
		{
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}

	return true;
}

void ModulePowerUps::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
	{
		// Always destroy particles that collide
		if (powerUps[i] != nullptr && c2->type == Collider::PLAYER_HITBOX)
		{
			powerUps[i]->isAlive = false;
			delete powerUps[i];
			powerUps[i] = nullptr;
			break;
		}

	}
}

UpdateResult ModulePowerUps::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
	{
		PowerUp* powerUp = powerUps[i];

		if (powerUp == nullptr)	continue;

		// Call Power Ups Update. If it has reached its lifetime, destroy it
		if (powerUp->Update() == false)
		{
			delete powerUps;
			powerUps[i] = nullptr;
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePowerUps::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
	{
		PowerUp* powerUp = powerUps[i];

		if (powerUp != nullptr && powerUp->isAlive)
		{
			App->render->Blit(texture, powerUp->position.x, powerUp->position.y, &(powerUp->anim.GetCurrentFrame()));
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePowerUps::AddPowerUp(const PowerUp& powerUp, int id, int x, int y,  Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
	{
		//Finding an empty slot for a new particle
		if (powerUps[i] == nullptr)
		{
			PowerUp* p = new PowerUp(powerUp);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;
			p->id = id;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			powerUps[i] = p;
			break;
		}
	}
}
