#ifndef __MODULE_POWER_UP_H__
#define __MODULE_POWER_UP_H__

#include "Module.h"

#include "Globals.h"
#include "PowerUps.h"
#include "Collider.h"
#include "p2Point.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class ModulePowerUp : public Module
{
public:
	
	ModulePowerUp(bool startEnabled);

	
	~ModulePowerUp();

	
	bool Start() override;

	
	UpdateResult Update() override;

	
	UpdateResult PostUpdate() override;

	
	bool CleanUp() override;

	
	void OnCollision(Collider* c1, Collider* c2) override;

	
	void AddParticle(const Power_Up& power_up, uint position, Collider::Type colliderType = Collider::Type::NONE);


private:
	
	SDL_Texture* texture = nullptr;
	

};

#endif 