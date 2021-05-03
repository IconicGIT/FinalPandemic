#ifndef __SECONDSCENE_H__
#define __SECONDSCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SecondScene : public Module
{
public:
	// Constructor
	SecondScene(bool startEnabled);

	// Destructor
	~SecondScene();

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

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* hTexture = nullptr;
};

#endif	// __SECONDSCENE_H__