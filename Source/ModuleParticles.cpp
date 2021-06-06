#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "Globals.h"

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
	

	playerBullet1[0].anim.PushBack({ 6, 175, 3, 8 });
	playerBullet1[1].anim.PushBack({ 17, 199, 6, 6 });
	playerBullet1[2].anim.PushBack({ 5, 200, 8, 3 });
	playerBullet1[3].anim.PushBack({ 25, 187, 6, 6 });
	playerBullet1[4].anim.PushBack({ 16, 187, 3, 8 });
	playerBullet1[5].anim.PushBack({ 7, 187, 6, 6 });
	playerBullet1[6].anim.PushBack({ 26, 176, 8, 3 });
	playerBullet1[7].anim.PushBack({ 16, 175, 6, 6 });

	for (int i = 0; i < 8; i++) 
	{
		playerBullet1[i].speed.x = 6;
		playerBullet1[i].speed.y = 6;
		playerBullet1[i].lifetime = 20;
		playerBullet1[i].anim.speed = 0;
		playerBullet1[i].anim.loop = false;
	}

	dust_particle.anim.PushBack({ 270,232,32,32 });
	dust_particle.anim.PushBack({ 302,232,32,32 });
	dust_particle.anim.PushBack({ 334,232,32,32 });
	dust_particle.anim.PushBack({ 366,232,32,32 });
	dust_particle.anim.PushBack({ 270,264,32,32 });
	dust_particle.anim.PushBack({ 302,264,32,32 });
	dust_particle.anim.loop = false;
	dust_particle.anim.speed = 0.2f;

	EnemyBullet.anim.PushBack({ 232, 103, 16, 12 });
	EnemyBullet.anim.PushBack({ 249, 103, 16, 12 });
	EnemyBullet.speed.x = 5;
	EnemyBullet.speed.y = 5;
	EnemyBullet.lifetime = 180;
	EnemyBullet.anim.speed = 0.2f;
	
	Boss1BulletR.anim.PushBack({ 126,275,1,10 });
	Boss1BulletR.lifetime = 24;
	Boss1BulletR.anim.speed = 1;
	Boss1BulletR.anim.loop = false;
	Boss1BulletR.speed.y = 5;
	Boss1BulletR.speed.x = -1;

	Boss1BulletL.anim.PushBack({ 126,275,1,10 });
	Boss1BulletL.lifetime = 24;
	Boss1BulletL.anim.speed = 1;
	Boss1BulletL.anim.loop = false;
	Boss1BulletL.speed.y = 5;
	Boss1BulletL.speed.x = 1;

	Explosion1.anim.PushBack({ 103,0,32,33 });
	Explosion1.anim.PushBack({ 135,0,32,33 });
	Explosion1.anim.PushBack({ 167,0,32,33 });
	Explosion1.anim.PushBack({ 199,0,32,33 });
	Explosion1.anim.loop = false;
	Explosion1.anim.speed = 0.2f;

	Explosion2Small.anim.PushBack({ 197,149,32,28 });
	Explosion2Small.anim.PushBack({ 197,247,32,28 });
	Explosion2Small.anim.PushBack({ 197,302,32,28 });
	Explosion2Small.anim.PushBack({ 197,356,32,28 });
	Explosion2Small.anim.loop = false;
	Explosion2Small.anim.speed = 0.2f;


	Explosion2Big.anim.PushBack({ 189,184,48,41 });
	Explosion2Big.anim.PushBack({ 239,184,48,41 });
	Explosion2Big.anim.PushBack({ 294,184,48,41 });
	Explosion2Big.anim.PushBack({ 350,184,48,41 });
	Explosion2Big.anim.loop = false;
	Explosion2Big.anim.speed = 0.2f;

	BulletEnd.anim.PushBack({ 0,274,12,12 });
	BulletEnd.anim.PushBack({ 12,274,12,12 });
	BulletEnd.anim.PushBack({ 24,274,12,12 });
	BulletEnd.anim.PushBack({ 35,274,12,12 });
	BulletEnd.anim.PushBack({ 48,274,12,12 });
	BulletEnd.anim.loop = false;
	BulletEnd.anim.speed = 0.4f;

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
	int max = MAX_ACTIVE_PARTICLES;
	bool loopDone = false;
 	for (uint i = deleteParticleIndex; i < max; ++i)
	{
		
		bool deleted = false;
		if (particles[i] != nullptr && particles[i]->collider != nullptr)
		{
 			////LOG("particle index: %i", deleteParticleIndex);
			switch (particles[i]->collider->type) {
			case Collider::PLAYER_SHOT:
			
				// Always destroy particles that collide
 				if (particles[i] != nullptr && c2->type == Collider::BULLET_WALL)
				{
					particles[i]->collider->pendingToDelete = true;
					particles[i]->isAlive = false;
					delete particles[i];
					particles[i] = nullptr;
					deleted = true;
					
				}
			
				if (particles[i] != nullptr && c2->type == Collider::ENEMY)
				{
					particles[i]->collider->pendingToDelete = true;
					particles[i]->isAlive = false;
					delete particles[i];
					particles[i] = nullptr;
					deleted = true;
					
					
				}
				break;
			
			case Collider::ENEMY_SHOT:
				// Always destroy particles that collide
				if (particles[i] != nullptr && c2->type == Collider::BULLET_WALL)
				{
					
					particles[i]->isAlive = false;
					particles[i]->collider->pendingToDelete = true;
					delete particles[i];
					particles[i] = nullptr;
					deleted = true;
					
				}
			
				if (particles[i] != nullptr && c2->type == Collider::PLAYER_HITBOX)
				{
					
					particles[i]->isAlive = false;
					particles[i]->collider->pendingToDelete = true;
					delete particles[i];
					particles[i] = nullptr;
					deleted = true;
					//Cause damage to enemy;
					//
					//
					
				}
				break;
			

			default:
				//// Always destroy particles that collide
				//if (particles[i] != nullptr && c2->type == Collider::WALL)
				//{
				//	particles[i]->isAlive = false;
				//	delete particles[i];
				//	particles[i] = nullptr;
				//	break;
				//}
				//
				//if (particles[i] != nullptr && c2->type == Collider::ENEMY)
				//{
				//	particles[i]->isAlive = false;
				//	delete particles[i];
				//	particles[i] = nullptr;
				//	//Cause damage to enemy;
				//	//
				//	//
				//	break;
				//}
				break;

			}

			
		}
		if (deleteParticleIndex + 1 == MAX_ACTIVE_PARTICLES) {
			deleteParticleIndex = 0;
		}
		else {
			if (deleted) deleteParticleIndex = i;
		}



		if (i == max - 1 && !loopDone) {
			i = -1;
			
			max = deleteParticleIndex;
			loopDone = true;
		}
		if (deleted) break;
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
			LOG("fin upd");
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
			LOG("particle created");
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;
			p->direction = direction;
			p->id = id;

			//Adding the particle's collider
 			if (colliderType != Collider::Type::NONE) 
			{
				
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
				if (colliderType == Collider::ENEMY_SHOT) LOG("enemy bullet fired");
				if (colliderType == Collider::PLAYER_SHOT) LOG("player bullet fired");
			}
			particles[i] = p;
			break;
		}
	}
}
