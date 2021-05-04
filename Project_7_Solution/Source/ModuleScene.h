#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene(bool startEnabled);

	//Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* tTexture = nullptr;

	Collider* bottomCol;
	
	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;



	uint32_t startTime;

	uint32_t currentTime;
	int counterMusic;
	int repetition;

	double elapsedTime; // Convert to seconds.
};

#endif