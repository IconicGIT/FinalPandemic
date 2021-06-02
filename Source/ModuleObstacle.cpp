
#include "ModuleObstacle.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"

#include "SDL/include/SDL_timer.h"


ModuleObstacle::ModuleObstacle(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
		obstacles[i] = nullptr;
}

ModuleObstacle::~ModuleObstacle()
{

}

bool ModuleObstacle::Start()
{
	LOG("Loading Obstacles");
	texture = App->textures->Load("Assets/Sprites/items_and_particles.png");

	
	Box.anim.PushBack({ 1, 115, 25, 18 });
	Box.anim.loop = true;
	Box.anim.speed = 1.0f;
	Box.life = 3;
	//

	return true;
}



bool ModuleObstacle::CleanUp()
{
	LOG("Unloading power ups");

	// Delete all remaining active power ups on application exit
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
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
	
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
	{
		
		if (obstacles[i] != nullptr && c2->type == Collider::PLAYER_SHOT) /////////////////////
		{
			//if (life <=0)
			//{
				obstacles[i]->isAlive = false;
				delete obstacles[i];
				obstacles[i] = nullptr;
				break;
			//}
		}
	}
}

UpdateResult ModuleObstacle::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
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
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
	{
		Obstacle* obstacle = obstacles[i];

		if (obstacle != nullptr && obstacle->isAlive)
		{
			App->render->Blit(texture, obstacle->position.x, obstacle->position.y, &(obstacle->anim.GetCurrentFrame()));
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleObstacle::AddObstacle(const Obstacle& obstacle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_POWER_UPS; ++i)
	{
		//Finding an empty slot for a new particle
		if (obstacles[i] == nullptr)
		{
			Obstacle* o = new Obstacle(obstacle);

			o->frameCount = -(int)delay;
			o->position.x = x;
			o->position.y = y;
			

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				o->collider = App->collisions->AddCollider(o->anim.GetCurrentFrame(), colliderType, this);

			obstacles[i] = o;
			break;
		}
	}
}
