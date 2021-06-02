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

	// Points
	PowerUp Medal1;
	PowerUp Medal2;
	PowerUp Medal3;

	// Player Shots
	PowerUp MachineGun;
	PowerUp FlameThrower;
	PowerUp Shotgun; 
	PowerUp GrenadeLouncher;

	// MERCS Bomb
	PowerUp Bomb;
	PowerUp Pow;

	// Health
	PowerUp TotalHealing;
	PowerUp MediumMedickit;
	PowerUp MaxMedickit;
	PowerUp Food1;
	PowerUp Food2;
	PowerUp Food3;
	PowerUp Food4;

	// Vehicles
	PowerUp Jeep;// life of the jeep = 6
};

#endif
