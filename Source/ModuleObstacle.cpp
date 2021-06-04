
#include "ModuleObstacle.h"
#include "ModulePowerUps.h"
#include "PowerUps.h"
#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"

#include "SDL/include/SDL_timer.h"


ModuleObstacle::ModuleObstacle(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_OBSTACLES; ++i)
		obstacles[i] = nullptr;
}

ModuleObstacle::~ModuleObstacle()
{

}

bool ModuleObstacle::Start()
{
	LOG("Loading Obstacles");
	texture = App->textures->Load("Assets/Sprites/items_and_particles.png");

	
	Box.anim.PushBack({ 0, 0, 28, 32 });
	Box.anim.loop = true;
	Box.anim.speed = 1.0f;
	Box.life = 3;
	

	return true;
}



bool ModuleObstacle::CleanUp()
{
	LOG("Unloading power ups");
	
	for (uint i = 0; i < MAX_ACTIVE_OBSTACLES; ++i)
	{
		if (obstacles[i] != nullptr)
		{
			delete obstacles[i];
			obstacles[i] = nullptr;
		}
	}

	return true;
}

void ModuleObstacle::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::PLAYER_SHOT)
	{
		Box.life--;

		switch (Box.life)
		{
		case 2:
			Box.anim.PushBack({ 1, 34, 29, 32 });
			break;
		case 1:
			Box.anim.PushBack({ 1, 70, 28, 32 });
			break;
		case 0:
			Box.isAlive = false;

			switch (Box.id)
			{
			case 0:
				App->powerUps->AddPowerUp(App->powerUps->Medal1, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 1:
				App->powerUps->AddPowerUp(App->powerUps->Medal2, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 2:
				App->powerUps->AddPowerUp(App->powerUps->Medal3, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 3:
				App->powerUps->AddPowerUp(App->powerUps->MachineGun, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 4:
				App->powerUps->AddPowerUp(App->powerUps->FlameThrower, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 5:
				App->powerUps->AddPowerUp(App->powerUps->Shotgun, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 6:
				App->powerUps->AddPowerUp(App->powerUps->GrenadeLouncher, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 7:
				App->powerUps->AddPowerUp(App->powerUps->Bomb, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 8:
				App->powerUps->AddPowerUp(App->powerUps->Pow, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 9:
				App->powerUps->AddPowerUp(App->powerUps->TotalHealing, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 10:
				App->powerUps->AddPowerUp(App->powerUps->MediumMedickit, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 11:
				App->powerUps->AddPowerUp(App->powerUps->MaxMedickit, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 12:
				App->powerUps->AddPowerUp(App->powerUps->Food1, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 13:
				App->powerUps->AddPowerUp(App->powerUps->Food2, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 14:
				App->powerUps->AddPowerUp(App->powerUps->Food3, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			case 15:
				App->powerUps->AddPowerUp(App->powerUps->Food4, 0, Box.position.x, Box.position.y, Collider::Type::POWER_UP, 0);
				break;
			}

			break;
		}
	}
	
	
	for (uint i = 0; i < MAX_ACTIVE_OBSTACLES; ++i)
	{
		
		if (obstacles[i] != nullptr && c2->type == Collider::PLAYER_SHOT) /////////////////////
		{
			
			obstacles[i]->isAlive = false;
			delete obstacles[i];
			obstacles[i] = nullptr;
			break;
			
		}
	}
}

UpdateResult ModuleObstacle::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_OBSTACLES; ++i)
	{
		Obstacle* obstacle = obstacles[i];

		if (obstacle == nullptr)	continue;

		// Call Power Ups Update. If it has reached its lifetime, destroy it
		if (obstacle->Update() == false)
		{

			delete obstacles[i];
			obstacles[i] = nullptr;
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleObstacle::PostUpdate()
{
	for (uint i = 0; i < MAX_ACTIVE_OBSTACLES; ++i)
	{
		Obstacle* obstacle = obstacles[i];

		if (obstacle != nullptr && obstacle->isAlive)
		{
			App->render->Blit(texture, obstacle->position.x, obstacle->position.y, &(obstacle->anim.GetCurrentFrame()));
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleObstacle::AddObstacle(const Obstacle& obstacle, int x, int y, int _id, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0)
{
	for (uint i = 0; i < MAX_ACTIVE_OBSTACLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (obstacles[i] == nullptr)
		{
			Obstacle* o = new Obstacle(obstacle);

			o->frameCount = -(int)delay;
			o->position.x = x;
			o->position.y = y;
			o->id = _id;
			

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				o->collider = App->collisions->AddCollider(o->anim.GetCurrentFrame(), colliderType, this);

			obstacles[i] = o;
			break;
		}
	}
}
