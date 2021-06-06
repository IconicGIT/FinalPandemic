#ifndef __THIRDSCENE_H__
#define __THIRDSCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ThirdScene : public Module
{
public:
	// Constructor
	ThirdScene(bool startEnabled);
	SDL_Texture* texture = nullptr;
	// Destructor
	~ThirdScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	bool CleanUp() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;
	char txtCredits[10] = { "\0" };
	
	int creditsFont = -1;
	
public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bTexture = nullptr;
	uint creditFX = 0;
};

#endif	// __THIRDSCENE_H__