#pragma once
#pragma once

#ifndef __MODULE_POWERUPS_H__
#define __MODULE_POWERUPS_H__

#include "Module.h"

#include "Globals.h"
#include "Obstacle.h"
#include "Collider.h"

#define MAX_ACTIVE_POWER_UPS 10

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

	void AddObstacle(const Obstacle& obstacle,  int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);


private:

	SDL_Texture* texture = nullptr;


	Obstacle* obstacles[MAX_ACTIVE_POWER_UPS] = { nullptr };

public:

	Obstacle Box;
	Obstacle House;
	Obstacle Palms;
};

#endif

