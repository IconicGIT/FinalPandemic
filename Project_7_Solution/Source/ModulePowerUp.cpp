#include "ModulePowerUp.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"

#include "SDL/include/SDL_timer.h"

ModulePowerUp::ModulePowerUp(bool startEnabled) : Module(startEnabled)
{
	//for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	//	particles[i] = nullptr;
}

ModulePowerUp::~ModulePowerUp()
{

}

bool ModulePowerUp::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/items_and_particles.png");


	return true;
}

bool ModulePowerUp::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	//for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	//{
	//	if (particles[i] != nullptr)
	//	{
	//		delete particles[i];
	//		particles[i] = nullptr;
	//	}
	//}

	return true;
}