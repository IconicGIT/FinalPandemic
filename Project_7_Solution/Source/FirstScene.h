#ifndef __FIRSTSCENE_H__
#define __FIRSTSCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class FirstScene : public Module
{
public:
	// Constructor
	FirstScene(bool startEnabled);

	// Destructor
	~FirstScene();

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

	int counter = 5;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* hTexture = nullptr;
};

#endif	// __FIRSTSCENE_H__