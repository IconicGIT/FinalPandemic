#pragma once
#pragma once

#ifndef __MODULE_POWERUPS_H__
#define __MODULE_POWERUPS_H__

#include "Module.h"

#include "Globals.h"
#include "PowerUps.h"
#include "Collider.h"

#define MAX_ACTIVE_POWER_UPS 10

struct SDL_Texture;
struct Collider;

class ModulePowerUps : public Module
{
public:

	ModulePowerUps(bool startEnabled);

	~ModulePowerUps();

	bool Start() override;


	UpdateResult Update() override;


	UpdateResult PostUpdate() override;

	bool CleanUp() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	void AddPowerUp(const PowerUp& powerUp, int id, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);


private:

	SDL_Texture* texture = nullptr;


	PowerUp* powerUps[MAX_ACTIVE_POWER_UPS] = { nullptr };

public:


	PowerUp Medal1;
	PowerUp MachineGun;
};

#endif
