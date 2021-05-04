#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/items_and_particles.png");


	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	laser.anim.PushBack({ 232, 103, 16, 12 });
	laser.anim.PushBack({ 249, 103, 16, 12 });
	laser.speed.x = 5;
	laser.lifetime = 180;
	laser.anim.speed = 0.2f;

	PlayerBullet1[0].anim.PushBack({ 6, 175, 3, 8 });
	PlayerBullet1[1].anim.PushBack({ 17, 199, 6, 6 });
	PlayerBullet1[2].anim.PushBack({ 5, 200, 8, 3 });
	PlayerBullet1[3].anim.PushBack({ 25, 187, 6, 6 });
	PlayerBullet1[4].anim.PushBack({ 16, 187, 3, 8 });
	PlayerBullet1[5].anim.PushBack({ 7, 187, 6, 6 });
	PlayerBullet1[6].anim.PushBack({ 26, 176, 8, 3 });
	PlayerBullet1[7].anim.PushBack({ 16, 175, 6, 6 });

	for (int i = 0; i < 8; i++) 
	{
		PlayerBullet1[i].speed.x = 10;
		PlayerBullet1[i].speed.y = 10;
		PlayerBullet1[i].lifetime = 180;
		PlayerBullet1[i].anim.speed = 0;
		PlayerBullet1[i].anim.loop = false;
	}


	

	EnemyBullet.anim.PushBack({ 232, 103, 16, 12 });
	EnemyBullet.anim.PushBack({ 249, 103, 16, 12 });
	EnemyBullet.speed.x = 5;
	EnemyBullet.speed.y = 5;
	EnemyBullet.lifetime = 180;
	EnemyBullet.anim.speed = 0.2f;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
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
		if (particles[i] != nullptr && c2->type == Collider::WALL )
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}

		if (particles[i] != nullptr && c2->type == Collider::ENEMY)
		{
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
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
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
