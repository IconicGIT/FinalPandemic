#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_Car.h"
#include "Enemy_Soldier.h"
#include "Enemy_Mech.h"
#include "Boss1.h"

#define SPAWN_MARGIN 300


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/Sprites/enemy_sprites.png");
	tCar = App->textures->Load("Assets/Sprites/enemy_car.png");
	tBoss_1 = App->textures->Load("Assets/Sprites/harrier_jet.png");
	enemyDestroyedFx = App->audio->LoadFx("");

	return true;
}

UpdateResult ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			//if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			//{
			//	LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
			//
			//	delete enemies[i];
			//	enemies[i] = nullptr;
			//}

			if (enemies[i]->timeAlive <= 0 && enemies[i]->inmortal == false) {
			
			
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
			
				delete enemies[i];
				enemies[i] = nullptr;
			
			}

		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case ENEMY_TYPE::CAR:
					enemies[i] = new Enemy_Car(info.x, info.y);
					enemies[i]->texture = tCar;
					break;
				case ENEMY_TYPE::SOLDIER:
					enemies[i] = new Enemy_Soldier(info.x, info.y);
					enemies[i]->texture = texture;
					break;
				case ENEMY_TYPE::BOSS_1:
					enemies[i] = new Enemy_Boss01(info.x, info.y);
					enemies[i]->texture = tBoss_1;
					break;
				case ENEMY_TYPE::MECH:
					enemies[i] = new Enemy_Mech(info.x, info.y);
					enemies[i]->texture = texture;
					break;
			}
			
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		//if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		//{
		//Notify the enemy of a collision
		if (enemies[i] != nullptr) {
			enemies[i]->OnCollision(c2);
		}
		//
		//	delete enemies[i];
		//	enemies[i] = nullptr;
		//	break;
		//}
	}
}