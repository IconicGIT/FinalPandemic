#pragma once
#pragma once

#ifndef __MODULE_OBSTACLES_H__
#define __MODULE_OBSTACLES_H__

#include "Module.h"

#include "Globals.h"
#include "Obstacle.h"
#include "Collider.h"

#define MAX_ACTIVE_OBSTACLES 20

struct SDL_Texture;
struct Collider;

class ModuleObstacle : public Module
{
public:

	ModuleObstacle(bool startEnabled);

	~ModuleObstacle();

	bool Start() override;


	UpdateResult Update() override;


	UpdateResult PostUpdate() override;

	bool CleanUp() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	void AddObstacle(const Obstacle& obstacle,  int x, int y, int id, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);
	//void AddPowerUp(const Obstacle& obstacle, int x, int y, int id, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);


private:

	SDL_Texture* texture = nullptr;


	Obstacle* obstacles[MAX_ACTIVE_OBSTACLES] = { nullptr };

public:

	Obstacle Box;
	//Obstacle House;
	//Obstacle Palms;
	//Obstacle Wall;
};

#endif

