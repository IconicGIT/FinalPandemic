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
		particles[i] = nullptr;
}

ModulePowerUps::~ModulePowerUps()
{

}

bool ModulePowerUps::Start()
{
	LOG("Loading Power Ups");
	texture = App->textures->Load("Assets/Sprites/items_and_particles.png");

	Medal1.anim.PushBack({ 274, 296, 33, 30 });// TODO
	Medal1.anim.loop = true;
	Medal1.anim.speed = 1.0f;
	Medal1.lifetime = 300;

	MachineGun.anim.PushBack({ 274, 296, 33, 30 });// TODO
	MachineGun.anim.loop = true;
	MachineGun.anim.speed = 1.0f;
	MachineGun.lifetime = 300;

	return true;
}

/*

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && c2->type == Collider::WALL)
		{
			particles[i]->isAlive = false;
			delete particles[i];
			particles[i] = nullptr;
			break;
		}

		if (particles[i] != nullptr && c2->type == Collider::ENEMY)
		{
			particles[i]->isAlive = false;
			delete particles[i];
			particles[i] = nullptr;
			//Cause damage to enemy;
			//
			//
			break;
		}
	}
}

UpdateResult ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int id, int x, int y, int direction, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;
			p->direction = direction;
			p->id = id;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}
*/