#include "ModulePowerUps.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"

#include "SDL/include/SDL_timer.h"

#define LIFETIME 30000000000000000

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

	// Medals
	Medal1.anim.PushBack({ 1, 115, 25, 18 }); 
	Medal1.anim.loop = true;
	Medal1.anim.speed = 1.0f;
	Medal1.lifetime = LIFETIME;

	Medal2.anim.PushBack({ 29, 115, 24, 19 });
	Medal2.anim.loop = true;
	Medal2.anim.speed = 1.0f;
	Medal2.lifetime = LIFETIME;

	Medal3.anim.PushBack({ 60, 115, 24, 17 });
	Medal3.anim.loop = true;
	Medal3.anim.speed = 1.0f;
	Medal3.lifetime = LIFETIME;
	 
	// Weapons
	MachineGun.anim.PushBack({ 1, 51, 26, 24 }); 
	MachineGun.anim.loop = true;
	MachineGun.anim.speed = 1.0f;
	MachineGun.lifetime = LIFETIME;

	FlameThrower.anim.PushBack({ 31, 48, 24, 24 });
	FlameThrower.anim.loop = true;
	FlameThrower.anim.speed = 1.0f;
	FlameThrower.lifetime = LIFETIME;

	Shotgun.anim.PushBack({ 91, 51, 24, 23 });
	Shotgun.anim.loop = true;
	Shotgun.anim.speed = 1.0f;
	Shotgun.lifetime = LIFETIME;
	
	GrenadeLouncher.anim.PushBack({ 62, 50, 24, 23 });
	GrenadeLouncher.anim.loop = true;
	GrenadeLouncher.anim.speed = 1.0f;
	GrenadeLouncher.lifetime = LIFETIME;

	// Bomb

	Bomb.anim.PushBack({ 148, 40, 24, 32 });
	Bomb.anim.PushBack({ 177, 40, 24, 32 });
	Bomb.anim.PushBack({ 206, 40, 24, 32 });
	Bomb.anim.loop = false;
	Bomb.anim.speed = 1.0f;
	Bomb.lifetime = LIFETIME;

	Bomb.anim.PushBack({ 123, 50, 19, 24 });
	Bomb.anim.loop = true;
	Bomb.anim.speed = 1.0f;
	Bomb.lifetime = LIFETIME;

	// Health

	TotalHealing.anim.PushBack({ 154, 84, 24, 19 });
	TotalHealing.anim.loop = true;
	TotalHealing.anim.speed = 1.0f;
	TotalHealing.lifetime = LIFETIME;

	MediumMedickit.anim.PushBack({ 103, 80, 20, 23 });
	MediumMedickit.anim.loop = true;
	MediumMedickit.anim.speed = 1.0f;
	MediumMedickit.lifetime = LIFETIME;

	MaxMedickit.anim.PushBack({ 128, 80, 20, 23 });
	MaxMedickit.anim.loop = true;
	MaxMedickit.anim.speed = 1.0f;
	MaxMedickit.lifetime = LIFETIME;

	Food1.anim.PushBack({ 1, 86, 20, 17 });
	Food1.anim.loop = true;
	Food1.anim.speed = 1.0f;
	Food1.lifetime = LIFETIME;

	Food2.anim.PushBack({ 28, 84, 15, 18 });
	Food2.anim.loop = true;
	Food2.anim.speed = 1.0f;
	Food2.lifetime = LIFETIME;

	Food3.anim.PushBack({ 49, 83, 22, 20 });
	Food3.anim.loop = true;
	Food3.anim.speed = 1.0f;
	Food3.lifetime = LIFETIME;

	Food4.anim.PushBack({ 76, 83, 21, 20 });
	Food4.anim.loop = true;
	Food4.anim.speed = 1.0f;
	Food4.lifetime = LIFETIME;

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

		//add powerups effects
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
			
			delete powerUps[i];
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
